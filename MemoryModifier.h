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

	UINT32 currentHealthHold;//当前血量
	UINT32 currentSpiritHold;//当前神
	UINT32 currentQiHold;//当前气

	UINT32 currentHealth;//当前血量-108
	UINT32 maximumHealth;//最大血量-20
	UINT32 currentSpirit;//当前神-104
	UINT32 maximumSpirit;//最大神-1C
	UINT32 currentQi;//当前气
	UINT32 maximumQi;//最大气

	UINT32 experience;//经验-24
	UINT32 currentGrade;//当前等级-28

	UINT32 attack;//攻击-18
	UINT32 defense;//防御-14
	UINT32 spiritual;//灵力-10
	UINT32 speed;//速度-C
	UINT32 luck;//运

	UINT32 thunder;//雷 金
	UINT32 wind;//风 木
	UINT32 water;//水
	UINT32 fire;//火
	UINT32 earth;//土
	UINT32 shade;//阴
	UINT32 sun;//阳

	UINT16 hand;//手持+0
	UINT16 head;//头戴+2
	UINT16 body;//身穿+4
	UINT16 foot;//脚踏+6
	UINT16 accessorie;//饰品+8

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
    DWORD      dwDesiredAccess, // 希望获得的访问权限
    BOOL       bInheritHandle, // 指明是否希望所获得的句柄可以继承
    DWORD      dwProcessId // 要访问的进程ID
    );

BOOL   WriteProcessMemory(
    HANDLE   hProcess,   //   要写进程的句柄
    LPVOID   lpBaseAddress,   //   写内存的起始地址
    LPVOID   lpBuffer,   //   写入数据的地址
    DWORD   nSize,   //   要写的字节数
    LPDWORD   lpNumberOfBytesWritten   //   实际写入的子节数
    );

BOOL   ReadProcessMemory(
    HANDLE   hProcess,   //   要读进程的句柄
    LPCVOID   lpBaseAddress,   //   读内存的起始地址
    LPVOID   lpBuffer,   //   读入数据的地址
    DWORD   nSize,   //   要读入的字节数
    LPDWORD   lpNumberOfBytesRead   //   实际读入的子节数
    );
*/
