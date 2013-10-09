/////////////////////////////////////////////////////////////////////////////
// This is a part of the PI-Software Sources
// Copyright (C) 1995-2002 PHYSIK INSTRUMENTE GmbH
// All rights reserved.
//
// This source code belongs to the Dll for the C-843 system

///////////////////////////////////////////////////////////////////////////// 
// Program: c843-Control DLL
//
// Developer: JKa
//  
// File: C843_GCS_DLL.h : main header file for the C-843 DLL
/////////////////////////////////////////////////////////////////////////////

#ifdef __USE_STDAFX_H
#include "stdafx.h"
#else
#include <windows.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#undef FUNC_DECL
#ifdef C843_DLL_EXPORTS
#define C843_FUNC_DECL __declspec(dllexport) WINAPI
#else
#define C843_FUNC_DECL __declspec(dllimport) WINAPI
#endif

/////////////////////////////////////////////////////////////////////////////
// DLL initialization and comm functions
int		C843_FUNC_DECL	C843_Connect(const int iBoardNumber);
BOOL	C843_FUNC_DECL	C843_IsConnected(const int iId);
void	C843_FUNC_DECL	C843_CloseConnection(const int iId);
int		C843_FUNC_DECL	C843_GetError(const int iId);
BOOL	C843_FUNC_DECL	C843_SetErrorCheck(const int iId, BOOL bErrorCheck);
BOOL	C843_FUNC_DECL	C843_TranslateError(int errNr, char* szBuffer, const int maxlen);
int		C843_FUNC_DECL	C843_GetCurrentBoardId(const int iBoardNumber);


/////////////////////////////////////////////////////////////////////////////
// general
BOOL C843_FUNC_DECL C843_qERR(const int iId, int* pnError);
BOOL C843_FUNC_DECL C843_qIDN(const int iId, char* buffer, const int maxlen);
BOOL C843_FUNC_DECL C843_INI(const int iId, char* const szAxes);
BOOL C843_FUNC_DECL C843_CLR(const int ID, char* const szAxes);

BOOL C843_FUNC_DECL C843_MOV(const int iId, char* const szAxes, double* pdValarray);
BOOL C843_FUNC_DECL C843_qMOV(const int iId, char* const szAxes, double* pdValarray);
BOOL C843_FUNC_DECL C843_MVR(const int iId, char* const szAxes, double* pdValarray);
BOOL C843_FUNC_DECL C843_IsMoving(const int iId, char* const szAxes, BOOL* pbValarray);
BOOL C843_FUNC_DECL C843_IsUserProfileActive(const int iId, char* const szAxes, BOOL* pbValarray);
BOOL C843_FUNC_DECL C843_qONT(const int iId, char* const szAxes, BOOL* pbValarray);

BOOL C843_FUNC_DECL C843_DFF(const int iId, char* const szAxes, double* pdValarray);
BOOL C843_FUNC_DECL C843_qDFF(const int iId, char* const szAxes, double* pdValarray);

BOOL C843_FUNC_DECL C843_DFH(const int iId, char* const szAxes);
BOOL C843_FUNC_DECL C843_qDFH(const int iId, char* const szAxes, double* pdValarray);
BOOL C843_FUNC_DECL C843_GOH(const int iId, char* const szAxes);

BOOL C843_FUNC_DECL C843_qPOS(const int iId, char* const szAxes, double* pdValarray);
BOOL C843_FUNC_DECL C843_POS(const int iId, char* const szAxes, double* pdValarray);

BOOL C843_FUNC_DECL C843_HLT(const int iId, char* const szAxes);
BOOL C843_FUNC_DECL C843_STP(const int iId);

BOOL C843_FUNC_DECL C843_qCST(const int iId, char* const szAxes, char* names, const int maxlen);
BOOL C843_FUNC_DECL C843_CST(const int iId, char* const szAxes, char* names);
BOOL C843_FUNC_DECL C843_qVST(const int iId, char* buffer, const int maxlen);
BOOL C843_FUNC_DECL C843_qTVI(const int iId, char* axes, const int maxlen);
BOOL C843_FUNC_DECL C843_SAI(const int iId, char* const szOldAxes, char* const szNewAxes);
BOOL C843_FUNC_DECL C843_qSAI(const int iId, char* axes, const int maxlen);
BOOL C843_FUNC_DECL C843_qSAI_ALL(const int iId, char* axes, const int maxlen);

BOOL C843_FUNC_DECL C843_SVO(const int iId, char* const szAxes, BOOL* pbValarray);
BOOL C843_FUNC_DECL C843_qSVO(const int iId, char* const szAxes, BOOL* pbValarray);
BOOL C843_FUNC_DECL C843_SMO(const int iId, char* const szAxes, int* pnValarray);
BOOL C843_FUNC_DECL C843_qSMO(const int iId, char* const szAxes, int* pnValarray);

BOOL C843_FUNC_DECL C843_VEL(const int iId, char* const szAxes, double* pdValarray);
BOOL C843_FUNC_DECL C843_qVEL(const int iId, char* const szAxes, double* pdValarray);

BOOL C843_FUNC_DECL C843_SPA(const int iId, char* const szAxes, int* iCmdarray, double* dValarray, char* szStageNames);
BOOL C843_FUNC_DECL C843_qSPA(const int iId, char* const szAxes, int* iCmdarray, double* dValarray, char* szStageNames, int iMaxNameSize);

BOOL C843_FUNC_DECL C843_qSRG(const int iId, char* const szAxes, int* iCmdarray, int* iValarray);


BOOL C843_FUNC_DECL C843_GetInputChannelNames(const int iId, char* szBuffer, const int maxlen);
BOOL C843_FUNC_DECL C843_GetOutputChannelNames(const int iId, char* szBuffer, const int maxlen);
BOOL C843_FUNC_DECL C843_DIO(const int iId, char* const szChannels, BOOL* pbValarray);
BOOL C843_FUNC_DECL C843_qDIO(const int iId, char* const szChannels, BOOL* pbValarray);
BOOL C843_FUNC_DECL C843_qTIO(const int iId, int* pINr, int* pONr);

BOOL C843_FUNC_DECL C843_STE(const int iId, char const  cAxis, double dOffset);
BOOL C843_FUNC_DECL C843_qSTE(const int iId, const char cAxis, const int iOffset, const int nrValues, double* pdValarray);

BOOL C843_FUNC_DECL C843_BRA(const int iId, char* const szAxes, BOOL* pbValarray);
BOOL C843_FUNC_DECL C843_qBRA(const int iId, char* szBuffer, const int maxlen);

BOOL C843_FUNC_DECL C843_qHLP(const int ID, char* buffer, const int maxlen);

/////////////////////////////////////////////////////////////////////////////
// String commands
BOOL C843_FUNC_DECL C843_C843Commandset(const int iId, char* const szCommand, char* szAwnser, int iMaxSize);
BOOL C843_FUNC_DECL C843_GcsCommandset(const int iId, char* const szCommand);
BOOL C843_FUNC_DECL C843_GcsGetAnswer(const int ID, char* szAnswer, const int bufsize);
BOOL C843_FUNC_DECL C843_GcsGetAnswerSize(const int ID, int* iAnswerSize);



/////////////////////////////////////////////////////////////////////////////
// QMC commands.
BOOL C843_FUNC_DECL C843_SetQMC(const int iId, BYTE bCmd, BYTE bAxis, int Param);
BOOL C843_FUNC_DECL C843_GetQMC(const int iId, BYTE bCmd, BYTE bAxis, int* pResult);
BOOL C843_FUNC_DECL C843_SetQMCA(const int iId, BYTE bCmd, BYTE bAxis, WORD Param1, int lParam2);
BOOL C843_FUNC_DECL C843_GetQMCA(const int iId, BYTE bCmd, BYTE bAxis, WORD lParam, int* pResult);



/////////////////////////////////////////////////////////////////////////////
// limits
BOOL C843_FUNC_DECL C843_MNL(const int iId,  char* const szAxes);
BOOL C843_FUNC_DECL C843_MPL(const int iId,  char* const szAxes);
BOOL C843_FUNC_DECL C843_REF(const int iId, char* const szAxes);
BOOL C843_FUNC_DECL C843_FRF(const int iId, char* const szAxes);
BOOL C843_FUNC_DECL C843_FPL(const int iId, char* const szAxes);
BOOL C843_FUNC_DECL C843_FNL(const int iId, char* const szAxes);
BOOL C843_FUNC_DECL C843_qREF(const int iId, char* const szAxes, BOOL* pbValarray);
BOOL C843_FUNC_DECL C843_qFRF(const int iId, char* const szAxes, BOOL* pbValarray);
BOOL C843_FUNC_DECL C843_qLIM(const int iId, char* const szAxes, BOOL* pbValarray);
BOOL C843_FUNC_DECL C843_IsReferencing(const int iId, char* const szAxes, BOOL* pbIsReferencing);
BOOL C843_FUNC_DECL C843_GetRefResult(const int iId, char* const szAxes, int* pnResult);
BOOL C843_FUNC_DECL C843_IsReferenceOK(const int iId, char* const szAxes, BOOL* pbValarray);
BOOL C843_FUNC_DECL C843_qTMN(const int iId, char* const szAxes, double* pdValarray);
BOOL C843_FUNC_DECL C843_qTMX(const int iId, char* const szAxes, double* pdValarray);
BOOL C843_FUNC_DECL C843_RON(const int iId, char* const szAxes, BOOL* pbValarray);
BOOL C843_FUNC_DECL C843_qRON(const int iId, char* const szAxes, BOOL* pbValarray);

/////////////////////////////////////////////////////////////////////////////
// User Profile Mode
BOOL C843_FUNC_DECL C843_UPB(const int iID, char* const szClusters, int* const iCmdarray, int* const iPararray, int* const iValarray);
BOOL C843_FUNC_DECL C843_UPD(const int iID, char* const szClusters, int* const iCmdarray, int* const iPararray, double* const dValarray);
BOOL C843_FUNC_DECL C843_UPC(const int iID, char* const szAxes,	char* const szClusters, int* const iCmdarray, int* const iPararray);
BOOL C843_FUNC_DECL C843_UPA(const int iID, char* const szClusters, int* const iCmdarray);
BOOL C843_FUNC_DECL C843_UPR(const int iID, char* const szAxes,	char* const szClusters, int* const iCmdarray);
BOOL C843_FUNC_DECL C843_qUPB(const int iID,char* const szClusters, int* const iCmdarray, int* const iPararray, int* iValarray);
BOOL C843_FUNC_DECL C843_qUPD(const int iID,char* const szClusters, int* const iCmdarray, int* const iPararray, double* dValarray);
BOOL C843_FUNC_DECL C843_qUPC(const int iID,char* const szClusters,char* szAxes, int* iCmdarray, int* iPararray);
BOOL C843_FUNC_DECL C843_qUPA(const int iID,char* const szClusters, int* const iCmdarray, int* iPararray);









/////////////////////////////////////////////////////////////////////////////
// Spezial
BOOL	C843_FUNC_DECL	C843_AddStage(const int iId, char* const szAxes);
BOOL	C843_FUNC_DECL	C843_RemoveStage(const int iId, char* szStageName);
BOOL	C843_FUNC_DECL C843_OpenUserStagesEditDialog(const int iId);
BOOL	C843_FUNC_DECL C843_OpenPiStagesEditDialog(const int iId);

#ifdef __cplusplus
}
#endif
