#include "pch.h"
#include "UserDll.h"

//��ʼ�����
HANDLE g_hPort = INVALID_HANDLE_VALUE;

int InitialCommuicationPort(void)
{
    DWORD hResult = FilterConnectCommunicationPort(MIN_PORT_NAME, 0, NULL, 0, NULL, &g_hPort);
    printf("������ͨ�Ŷ˿ڳ�ʼ��\n");
    if (hResult != S_OK)
    {
        return hResult;
        printf("ͨ�Ŷ˿ڳ�ʼ�����ɹ�\n");
    }
    printf("ͨ�Ŷ˿ڳ�ʼ���ɹ�\n");
    return 0;
}

int NPSendMessage(PVOID InputBuffer)
{
    DWORD bytesReturned = 0;
    DWORD hResult = 0;
    PCOMMAND_MESSAGE command_message = (PCOMMAND_MESSAGE)InputBuffer;

    printf("���뷢����Ϣ\n");
    hResult = FilterSendMessage(
        g_hPort, 
        command_message, 
        sizeof(COMMAND_MESSAGE), 
        NULL, 
        NULL, 
        &bytesReturned);

    if (hResult != S_OK)
    {
        return hResult;
    }
    return 0;
}

int NPGetMessage(PVOID InputBuffer)
{
    DWORD bytesReceived = 0;
    DWORD hResult = 0;
    PSCANNER_MESSAGE scannerMessage = (PSCANNER_MESSAGE)InputBuffer;
    hResult = FilterGetMessage(
        g_hPort,
        &scannerMessage->MessageHeader,
        sizeof(SCANNER_MESSAGE),
        NULL
    );
    printf("scanner message: %ls\n", scannerMessage->info.path);
    if (hResult != S_OK)
    {
        printf("%d\n", hResult);
        return hResult;
    }
    return 0;
}