#pragma once

#include <QtWidgets/QMainWindow>
#include <QTimer>
#include "ui_MemoryModifier.h"

#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <QMessageBox>
#include <QDebug>
#include <tchar.h>

class MemoryModifier : public QMainWindow
{
	Q_OBJECT
public:
	MemoryModifier(QWidget *parent = Q_NULLPTR);
	UINT32 GetDymThroughBase(UINT32 baseAddress, UINT32 Offset[], UINT32 len);
	void readAndSetInfo();
	void readAndSetInfoAT();
	void clearLineEdit();

	UINT32 currentHealthHold;//��ǰѪ��
	UINT32 currentSpiritHold;//��ǰ��
	UINT32 currentQiHold;//��ǰ��

	UINT32 currentHealth;//��ǰѪ��-108
	UINT32 maximumHealth;//���Ѫ��-20
	UINT32 currentSpirit;//��ǰ��-104
	UINT32 maximumSpirit;//�����-1C
	UINT32 currentQi;//��ǰ��
	UINT32 maximumQi;//�����

	UINT32 experience;//����-24
	UINT32 currentGrade;//��ǰ�ȼ�-28

	UINT32 attack;//����-18
	UINT32 defense;//����-14
	UINT32 spiritual;//����-10
	UINT32 speed;//�ٶ�-C
	UINT32 luck;//��

	UINT32 thunder;//�� ��
	UINT32 wind;//�� ľ
	UINT32 water;//ˮ
	UINT32 fire;//��
	UINT32 earth;//��
	UINT32 shade;//��
	UINT32 sun;//��

	UINT16 hand;//�ֳ�+0
	UINT16 head;//ͷ��+2
	UINT16 body;//��+4
	UINT16 foot;//��̤+6
	UINT16 accessorie;//��Ʒ+8

	UINT32 money;
	UINT32 z;
	UINT32 blue;
	UINT32 red;
	UINT32 green;
	UINT32 colours;
	UINT32 purple;
	UINT32 gold;

private slots:
	void on_modifyPushButton_clicked();
	void on_role1RadioButton_pressed();
	void on_role2RadioButton_pressed();
	void on_role3RadioButton_pressed();
	void on_role4RadioButton_pressed();
	void on_role5RadioButton_pressed();
	void on_experienceAddressLineEdit_textEdited(const QString& text);
	void on_currentHealthAddressLineEdit_textEdited(const QString& text);
	void on_currentSpiritAddressLineEdit_textEdited(const QString& text);

	void on_gameAddressATLineEdit_editingFinished();
    //void on_processIDLineEdit_editingFinished();
	void on_processGamePushButton_toggled(bool checked);
	void on_healthATCheckBox_stateChanged(int state);
	void on_qiATCheckBox_stateChanged(int state);
	void on_angryATCheckBox_stateChanged(int state);

	void ATTimerOut();
	void healthATTimerOut();
	void qiATTimerOut();
	void angryATTimerOut();

private:
	HWND hwnd_Game;
	DWORD processID;
	UINT64 dymnamicAddress;
	UINT64 dymnamicAddressAT;
	UINT64 roleExperienceAddress[5];
	quint8 currentRole;
	HANDLE hPro;
	QTimer* ATTimer;
	QTimer *healthATTimer;
	QTimer *qiATTimer;
	QTimer *angryATTimer;
	Ui::MemoryModifierClass ui;
};

/*
HANDLE OpenProcess(
    DWORD      dwDesiredAccess, // ϣ����õķ���Ȩ��
    BOOL       bInheritHandle, // ָ���Ƿ�ϣ������õľ�����Լ̳�
    DWORD      dwProcessId // Ҫ���ʵĽ���ID
    );

BOOL   WriteProcessMemory(
    HANDLE   hProcess,   //   Ҫд���̵ľ��
    LPVOID   lpBaseAddress,   //   д�ڴ����ʼ��ַ
    LPVOID   lpBuffer,   //   д�����ݵĵ�ַ
    DWORD   nSize,   //   Ҫд���ֽ���
    LPDWORD   lpNumberOfBytesWritten   //   ʵ��д����ӽ���
    );

BOOL   ReadProcessMemory(
    HANDLE   hProcess,   //   Ҫ�����̵ľ��
    LPCVOID   lpBaseAddress,   //   ���ڴ����ʼ��ַ
    LPVOID   lpBuffer,   //   �������ݵĵ�ַ
    DWORD   nSize,   //   Ҫ������ֽ���
    LPDWORD   lpNumberOfBytesRead   //   ʵ�ʶ�����ӽ���
    );
*/
