void CCamera::TDITest(unsigned short * * image, int XSize, int YSize, int Bin)
{
	IMAGELIST_HANDLE imagelist_handle;
	REGIONLIST_HANDLE regionlist_handle;
	IMAGE_HANDLE Image;
	FUNCTION = "camera_readout_ccd";
	LPCAMERA			pcamera = NULL;
	SYSPARAMS_HANDLE	params_handle = NULL;
	char				base_filename[80];
	BOOLEAN				result = FALSE;
	SYSPARAM			region;
	SYSPARAM			p_image;
	STRING				name_with_path = NULL;
	REGIONLIST_HANDLE	tregionlist_handle = NULL;

	int a,b;
	unsigned short *TDIBuffer, **TDIArray;
	unsigned short *Row;

	if (Bin != 1)
		return;

	TDIBuffer = new unsigned short[XSize * YSize * Bin];
	TDIArray  = new unsigned short*[XSize * Bin];
	for (a=0; a<XSize * Bin; ++a)
		TDIArray[a] = &TDIBuffer[a*YSize];
	camera_set_binning(m_hCamera,Bin,Bin);
	imagelist_handle = imagelist_new();
	regionlist_handle = regionlist_new();
	if (regionlist_append(regionlist_handle, 0,0,YSize,XSize,"Fred") == NULL) // change here for 1 row
		OnError();

	pcamera = camera_lock (m_hCamera);
	/* get filename for readout program */
	camprogs_get_basefile (&pcamera->programs, READOUT_GNAME, base_filename);
	/* make temporary copy of regionlist handle */
	tregionlist_handle = regionlist_handle;
	if (camera_readout_regions (m_hCamera, &tregionlist_handle))
	{
		/* setup sysparam values */
		region.data.ival	= (INT32)tregionlist_handle;
		p_image.data.ival		= (INT32)imagelist_handle;
		if ((params_handle = sysparams_new()) != NULL)
		{
			if (
			sysparams_append (params_handle,
					sysparam_make_ival (CCD_XSIZE, pcamera->ccd.xsize)) &&
				sysparams_append (params_handle,
					sysparam_make_ival (CCD_YSIZE, pcamera->ccd.ysize)) &&
				sysparams_append (params_handle,
					sysparam_make_ival (CCD_XBIN, pcamera->ccd.xbin)) &&
				sysparams_append (params_handle,
					sysparam_make_ival (CCD_YBIN, pcamera->ccd.ybin)) &&
				sysparams_append (params_handle,
					sysparam_make_pval (REGION_LIST, region.data.pval)) &&
				sysparams_append (params_handle,
					sysparam_make_pval (IMAGE_LIST, p_image.data.pval))
					)
			{
				/* allocate memory for images up front to ensure
				   sufficient memory available. generate the full
				   micro code filename. execute the specified
				   micro code file using the supplied parameters. */
				camera_allocate_all_images (m_hCamera, tregionlist_handle,
									imagelist_handle, params_handle);
				camera_system_filename (m_hCamera, base_filename, &name_with_path);
				server_execute (pcamera->server, name_with_path, params_handle);
			}
				sysparams_delete (params_handle);
		}
		result = camera_measure_iz (m_hCamera, imagelist_handle);
			/* free created regionlist handle */
		if (tregionlist_handle &&
						(regionlist_handle != tregionlist_handle))
		regionlist_delete (tregionlist_handle);
	}
	camera_unlock (m_hCamera);
	
	
	imagelist_head(imagelist_handle);
	Image = imagelist_get(imagelist_handle);
	for (a=0; a<XSize; ++a)
	{
		Row=(unsigned short*)image_lockraster(Image,a);
		if (Row == NULL)
			OnError();
		for (b=0; b<YSize; ++b)
			image[b][a] = Row[b];
	}
}
