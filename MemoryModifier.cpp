#include "MemoryModifier.h"

MemoryModifier::MemoryModifier(QWidget *parent) : QMainWindow(parent)
,currentRole(1)
{
	ui.setupUi(this);
	ATTimer = new QTimer(this);
	healthATTimer = new QTimer(this);
	qiATTimer = new QTimer(this);
	angryATTimer = new QTimer(this);

	ui.role1RadioButton->setChecked(true);
	for (int i = 0; i < 5; i++)
		roleExperienceAddress[i] = 0;

	connect(ATTimer, &QTimer::timeout, this, &MemoryModifier::ATTimerOut);
	connect(healthATTimer, &QTimer::timeout, this, &MemoryModifier::healthATTimerOut);
	connect(qiATTimer, &QTimer::timeout, this, &MemoryModifier::qiATTimerOut);
	connect(angryATTimer, &QTimer::timeout, this, &MemoryModifier::angryATTimerOut);
}

void MemoryModifier::on_experienceAddressLineEdit_textEdited(const QString& text)
{
	bool ok;
	dymnamicAddress = text.toLongLong(&ok, 16);
	switch (currentRole)
	{
	case 1:roleExperienceAddress[0] = dymnamicAddress; break;
	case 2:roleExperienceAddress[1] = dymnamicAddress; break;
	case 3:roleExperienceAddress[2] = dymnamicAddress; break;
	case 4:roleExperienceAddress[3] = dymnamicAddress; break;
	case 5:roleExperienceAddress[4] = dymnamicAddress; break;
	}
	readAndSetInfo();
}

void MemoryModifier::on_currentHealthAddressLineEdit_textEdited(const QString& text)
{
	bool ok;
	dymnamicAddress = text.toLongLong(&ok, 16) + 0xE4;
	switch (currentRole)
	{
	case 1:roleExperienceAddress[0] = dymnamicAddress; break;
	case 2:roleExperienceAddress[1] = dymnamicAddress; break;
	case 3:roleExperienceAddress[2] = dymnamicAddress; break;
	case 4:roleExperienceAddress[3] = dymnamicAddress; break;
	case 5:roleExperienceAddress[4] = dymnamicAddress; break;
	}
	readAndSetInfo();
}

void MemoryModifier::on_currentSpiritAddressLineEdit_textEdited(const QString& text)
{
	bool ok;
	dymnamicAddress = text.toLongLong(&ok, 16) + 0xE0;
	switch (currentRole)
	{
	case 1:roleExperienceAddress[0] = dymnamicAddress; break;
	case 2:roleExperienceAddress[1] = dymnamicAddress; break;
	case 3:roleExperienceAddress[2] = dymnamicAddress; break;
	case 4:roleExperienceAddress[3] = dymnamicAddress; break;
	case 5:roleExperienceAddress[4] = dymnamicAddress; break;
	}
	readAndSetInfo();
}

void MemoryModifier::on_role1RadioButton_pressed()
{
	currentRole = 1;
	dymnamicAddress = 0;
	clearLineEdit();
	dymnamicAddress = roleExperienceAddress[0];
	if (dymnamicAddress != 0)
		readAndSetInfoAT();
}
void MemoryModifier::on_role2RadioButton_pressed()
{
	currentRole = 2;
	dymnamicAddress = 0;
	clearLineEdit();
	dymnamicAddress = roleExperienceAddress[1];
	if (dymnamicAddress != 0)
		readAndSetInfoAT();
}
void MemoryModifier::on_role3RadioButton_pressed()
{
	currentRole = 3;
	dymnamicAddress = 0;
	clearLineEdit();
	dymnamicAddress = roleExperienceAddress[2];
	if (dymnamicAddress != 0)
		readAndSetInfoAT();
}
void MemoryModifier::on_role4RadioButton_pressed()
{
	currentRole = 4;
	dymnamicAddress = 0;
	clearLineEdit();
	dymnamicAddress = roleExperienceAddress[3];
	if (dymnamicAddress != 0)
		readAndSetInfoAT();
}
void MemoryModifier::on_role5RadioButton_pressed()
{
	currentRole = 5;
	dymnamicAddress = 0;
	clearLineEdit();
	dymnamicAddress = roleExperienceAddress[4];
	if (dymnamicAddress != 0)
		readAndSetInfoAT();
}

void MemoryModifier::clearLineEdit()
{
	ui.experienceAddressLineEdit->clear();
	ui.currentHealthAddressLineEdit->clear();
	ui.currentSpiritAddressLineEdit->clear();
	ui.maximumHealthLineEdit->clear();
	ui.maximumSpiritLineEdit->clear();
	ui.currentHealthLineEdit->clear();
	ui.currentSpiritLineEdit->clear();
	ui.experienceLineEdit->clear();
	ui.currentGradeLineEdit->clear();
	ui.attackLineEdit->clear();
	ui.defenseLineEdit->clear();
	ui.spiritualLineEdit->clear();
	ui.speedLineEdit->clear();
	ui.handLineEdit->clear();
	ui.headLineEdit->clear();
	ui.bodyLineEdit->clear();
	ui.footLineEdit->clear();
	ui.accessorieLineEdit->clear();
}

void MemoryModifier::readAndSetInfo()
{
	ReadProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x4), &maximumHealth, 4, NULL);
	ReadProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x8), &maximumSpirit, 4, NULL);
	ReadProcessMemory(hPro, (LPVOID)(dymnamicAddress - 0xE4), &currentHealth, 4, NULL);
	ReadProcessMemory(hPro, (LPVOID)(dymnamicAddress - 0xE0), &currentSpirit, 4, NULL);
	ReadProcessMemory(hPro, (LPVOID)(dymnamicAddress - 0x0), &experience, 4, NULL);
	ReadProcessMemory(hPro, (LPVOID)(dymnamicAddress - 0x4), &currentGrade, 4, NULL);
	ReadProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0xC), &attack, 4, NULL);
	ReadProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x10), &defense, 4, NULL);
	ReadProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x14), &spiritual, 4, NULL);
	ReadProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x18), &speed, 4, NULL);
	ReadProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x24), &hand, 2, NULL);
	ReadProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x26), &head, 2, NULL);
	ReadProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x28), &body, 2, NULL);
	ReadProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x2A), &foot, 2, NULL);
	ReadProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x2C), &accessorie, 2, NULL);

	ui.experienceAddressLineEdit->setText(QString::number(dymnamicAddress, 16));
	ui.currentHealthAddressLineEdit->setText(QString::number(dymnamicAddress - 0xE4, 16));
	ui.currentSpiritAddressLineEdit->setText(QString::number(dymnamicAddress - 0xE0, 16));
	ui.maximumHealthLineEdit->setText(QString::number(maximumHealth));
	ui.maximumSpiritLineEdit->setText(QString::number(maximumSpirit));
	ui.currentHealthLineEdit->setText(QString::number(currentHealth));
	ui.currentSpiritLineEdit->setText(QString::number(currentSpirit));
	ui.experienceLineEdit->setText(QString::number(experience));
	ui.currentGradeLineEdit->setText(QString::number(currentGrade));
	ui.attackLineEdit->setText(QString::number(attack));
	ui.defenseLineEdit->setText(QString::number(defense));
	ui.spiritualLineEdit->setText(QString::number(spiritual));
	ui.speedLineEdit->setText(QString::number(speed));
	ui.handLineEdit->setText(QString::number(hand));
	ui.headLineEdit->setText(QString::number(head));
	ui.bodyLineEdit->setText(QString::number(body));
	ui.footLineEdit->setText(QString::number(foot));
	ui.accessorieLineEdit->setText(QString::number(accessorie));
}

void MemoryModifier::on_modifyPushButton_clicked()
{
    //bool ok;
	if (ui.gameTabWidget->currentIndex() == 0)//龙珠Z：卡卡罗特
	{
		maximumHealth = ui.addHealthATLineEdit->text().toUInt();
		maximumSpirit = ui.addQiATLineEdit->text().toUInt();
		currentHealth = ui.healthATLineEdit->text().toUInt();
		currentSpirit = ui.qiATLineEdit->text().toUInt();
		currentQi = ui.angryATLineEdit->text().toUInt();
		experience = ui.experienceATLineEdit->text().toUInt();
		currentGrade = ui.gradeATLineEdit->text().toUInt();
		attack = ui.addGATKATLineEdit->text().toUInt();
		defense = ui.addGDefenseATLineEdit->text().toUInt();
		spiritual = ui.addQATKATLineEdit->text().toUInt();
		speed = ui.addQDefenseATLineEdit->text().toUInt();
		luck = ui.criticalATLineEdit->text().toUInt();

		money= ui.moneyATLineEdit->text().toUInt();
		blue = ui.blueATLineEdit->text().toUInt();
		red = ui.redATLineEdit->text().toUInt();
		green = ui.greenATLineEdit->text().toUInt();
		colours = ui.coloursATLineEdit->text().toUInt();
		purple = ui.purpleATLineEdit->text().toUInt();
		gold = ui.goldATLineEdit->text().toUInt();
		z = ui.zATLineEdit->text().toUInt();

		SIZE_T dwNumberOfBytesRead;	//存储之前的访问权限
		WriteProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x20), &maximumHealth, 4, &dwNumberOfBytesRead);
		WriteProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x24), &maximumSpirit, 4, &dwNumberOfBytesRead);
		WriteProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x10), &currentHealth, 4, &dwNumberOfBytesRead);
		WriteProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x14), &currentSpirit, 4, &dwNumberOfBytesRead);
		WriteProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x18), &currentQi, 4, &dwNumberOfBytesRead);
		WriteProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x8), &experience, 4, &dwNumberOfBytesRead);
		WriteProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x0), &currentGrade, 4, &dwNumberOfBytesRead);
		WriteProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x28), &attack, 4, &dwNumberOfBytesRead);
		WriteProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x2C), &defense, 4, &dwNumberOfBytesRead);
		WriteProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x30), &spiritual, 4, &dwNumberOfBytesRead);
		WriteProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x34), &speed, 4, &dwNumberOfBytesRead);
		WriteProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x38), &luck, 4, &dwNumberOfBytesRead);

		WriteProcessMemory(hPro, (LPVOID)(dymnamicAddressAT + 0x38), &money, 4, &dwNumberOfBytesRead);
		WriteProcessMemory(hPro, (LPVOID)(dymnamicAddressAT + 0x3C), &blue, 4, &dwNumberOfBytesRead);
		WriteProcessMemory(hPro, (LPVOID)(dymnamicAddressAT + 0x40), &red, 4, &dwNumberOfBytesRead);
		WriteProcessMemory(hPro, (LPVOID)(dymnamicAddressAT + 0x44), &green, 4, &dwNumberOfBytesRead);
		WriteProcessMemory(hPro, (LPVOID)(dymnamicAddressAT + 0x48), &colours, 4, &dwNumberOfBytesRead);
		WriteProcessMemory(hPro, (LPVOID)(dymnamicAddressAT + 0x4C), &purple, 4, &dwNumberOfBytesRead);
		WriteProcessMemory(hPro, (LPVOID)(dymnamicAddressAT + 0x50), &gold, 4, &dwNumberOfBytesRead);
        WriteProcessMemory(hPro, (LPVOID)(dymnamicAddressAT + 0x1D948), &z, 4, &dwNumberOfBytesRead);
	}
	else if (ui.gameTabWidget->currentIndex() == 1)//仙剑奇侠传续传
	{
		maximumHealth = ui.maximumHealthLineEdit->text().toUInt();
		maximumSpirit = ui.maximumSpiritLineEdit->text().toUInt();
		currentHealth = ui.currentHealthLineEdit->text().toUInt();
		currentSpirit = ui.currentSpiritLineEdit->text().toUInt();
		experience = ui.experienceLineEdit->text().toUInt();
		currentGrade = ui.currentGradeLineEdit->text().toUInt();
		attack = ui.attackLineEdit->text().toUInt();
		defense = ui.defenseLineEdit->text().toUInt();
		spiritual = ui.spiritualLineEdit->text().toUInt();
		speed = ui.speedLineEdit->text().toUInt();
		hand = ui.handLineEdit->text().toUInt();
		head = ui.headLineEdit->text().toUInt();
		body = ui.bodyLineEdit->text().toUInt();
		foot = ui.footLineEdit->text().toUInt();
		accessorie = ui.accessorieLineEdit->text().toUInt();

		SIZE_T dwNumberOfBytesRead;	//存储之前的访问权限

		WriteProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x4), &maximumHealth, 4, &dwNumberOfBytesRead);
		WriteProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x8), &maximumSpirit, 4, &dwNumberOfBytesRead);
		WriteProcessMemory(hPro, (LPVOID)(dymnamicAddress - 0xE4), &currentHealth, 4, &dwNumberOfBytesRead);
		WriteProcessMemory(hPro, (LPVOID)(dymnamicAddress - 0xE0), &currentSpirit, 4, &dwNumberOfBytesRead);
		WriteProcessMemory(hPro, (LPVOID)(dymnamicAddress - 0x0), &experience, 4, &dwNumberOfBytesRead);
		WriteProcessMemory(hPro, (LPVOID)(dymnamicAddress - 0x4), &currentGrade, 4, &dwNumberOfBytesRead);
		WriteProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0xC), &attack, 4, &dwNumberOfBytesRead);
		WriteProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x10), &defense, 4, &dwNumberOfBytesRead);
		WriteProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x14), &spiritual, 4, &dwNumberOfBytesRead);
		WriteProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x18), &speed, 4, &dwNumberOfBytesRead);
		WriteProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x24), &hand, 2, &dwNumberOfBytesRead);
		WriteProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x26), &head, 2, &dwNumberOfBytesRead);
		WriteProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x28), &body, 2, &dwNumberOfBytesRead);
		WriteProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x2A), &foot, 2, &dwNumberOfBytesRead);
		WriteProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x2C), &accessorie, 2, &dwNumberOfBytesRead);
	}

	/*int write_ = WriteProcessMemory(hPro, (LPVOID)(dymnamicAddress - 0xE0), &currentSpirit, 4, &dwNumberOfBytesRead);
	if (write_ == 0)
		QMessageBox::warning(this, tr("warning"), tr("Writing to memory value failed, please check permissions!"), QMessageBox::Cancel);*/
}

void MemoryModifier::on_processGamePushButton_toggled(bool checked)
{
	if (checked)
	{
		ui.processGamePushButton->setText(tr("Updating"));
		ATTimer->start(500);
	}
	else
	{
        ui.processGamePushButton->setText(tr("Stopped"));
		ATTimer->stop();
    }
}

//void MemoryModifier::on_processIDLineEdit_editingFinished()
//{
//	bool ok;
//	if (ui.gameTabWidget->currentIndex() == 0)
//		processID = ui.processIDLineEdit->text().toUInt(&ok, 16);
//	GetWindowThreadProcessId(hwnd_Game, &processID);
//	hPro = OpenProcess(PROCESS_ALL_ACCESS | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, FALSE, processID);
//}

void MemoryModifier::on_gameAddressATLineEdit_editingFinished()
{
	bool ok;
	dymnamicAddress = ui.gameAddressATLineEdit->text().toULongLong(&ok, 16) * 65536;
	dymnamicAddressAT = dymnamicAddress;
    roleExperienceAddress[0] = dymnamicAddress + 0x2B0;//悟空等级
    roleExperienceAddress[1] = dymnamicAddress + 0x548;//悟饭
    roleExperienceAddress[2] = dymnamicAddress + 0x7E0;//贝吉塔
    roleExperienceAddress[3] = dymnamicAddress + 0x14D8;//比克
    roleExperienceAddress[4] = dymnamicAddress + 0x1770;//特兰克斯
	dymnamicAddress = roleExperienceAddress[0];

    switch (ui.gameTabWidget->currentIndex())
    {
    case 0:hwnd_Game = FindWindow(NULL, _T("DRAGON BALL Z: KAKAROT  ")); break;
    //case 1:hwnd_Game = FindWindow(NULL, _T("仙剑续传")); break;
    }

    if (hwnd_Game == NULL)//如果无法获取句柄则报错
    {
        QMessageBox::warning(this, tr("warning"), tr("Unable to get process handle, please check if the process exists!"), QMessageBox::Cancel);
        return;
    }
    else
    {
        GetWindowThreadProcessId(hwnd_Game, &processID);
        qDebug() << "processID" << processID;
    }
    hPro = OpenProcess(PROCESS_ALL_ACCESS | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, FALSE, processID);
    if (hPro == 0)
    {
        QMessageBox::warning(this, tr("warning"), tr("Unable to get process handle!"), QMessageBox::Cancel);
        return;
    }
}

void MemoryModifier::ATTimerOut()
{
    readAndSetInfoAT();
}

void MemoryModifier::on_healthATCheckBox_stateChanged(int state)
{
	if (state)
	{
		ReadProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x10), &currentHealthHold, 4, NULL);
		healthATTimer->start(500);
	}
	else
		healthATTimer->stop();
}

void MemoryModifier::on_qiATCheckBox_stateChanged(int state)
{
	if (state)
	{
		ReadProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x14), &currentSpiritHold, 4, NULL);
		qiATTimer->start(500);
	}
	else
		qiATTimer->stop();
}

void MemoryModifier::on_angryATCheckBox_stateChanged(int state)
{
	qDebug() << state;
	if (state)
	{
		currentQiHold = 1000;
		angryATTimer->start(500);
	}
	else
		angryATTimer->stop();
}

void MemoryModifier::healthATTimerOut()
{
	SIZE_T dwNumberOfBytesRead;	//存储之前的访问权限
	WriteProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x10), &currentHealthHold, 4, &dwNumberOfBytesRead);
}

void MemoryModifier::qiATTimerOut()
{
	SIZE_T dwNumberOfBytesRead;	//存储之前的访问权限
	WriteProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x14), &currentSpiritHold, 4, &dwNumberOfBytesRead);
}

void MemoryModifier::angryATTimerOut()
{
	SIZE_T dwNumberOfBytesRead;	//存储之前的访问权限
	//WriteProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x18), &currentQiHold, 4, &dwNumberOfBytesRead);
	for (int i = 0; i < 5; i++)
		WriteProcessMemory(hPro, (LPVOID)(roleExperienceAddress[i] + 0x18), &currentQiHold, 4, &dwNumberOfBytesRead);
}

void MemoryModifier::readAndSetInfoAT()
{
	ReadProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x20), &maximumHealth, 4, NULL);
	ReadProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x24), &maximumSpirit, 4, NULL);
	ReadProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x10), &currentHealth, 4, NULL);
	ReadProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x14), &currentSpirit, 4, NULL);
	ReadProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x18), &currentQi, 4, NULL);
	ReadProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x8), &experience, 4, NULL);
	ReadProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x0), &currentGrade, 4, NULL);
	ReadProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x28), &attack, 4, NULL);
	ReadProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x2C), &defense, 4, NULL);
	ReadProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x30), &spiritual, 4, NULL);
	ReadProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x34), &speed, 4, NULL);
	ReadProcessMemory(hPro, (LPVOID)(dymnamicAddress + 0x38), &luck, 4, NULL);

	ReadProcessMemory(hPro, (LPVOID)(dymnamicAddressAT + 0x38), &money, 4, NULL);
	ReadProcessMemory(hPro, (LPVOID)(dymnamicAddressAT + 0x3C), &blue, 4, NULL);
	ReadProcessMemory(hPro, (LPVOID)(dymnamicAddressAT + 0x40), &red, 4, NULL);
	ReadProcessMemory(hPro, (LPVOID)(dymnamicAddressAT + 0x44), &green, 4, NULL);
	ReadProcessMemory(hPro, (LPVOID)(dymnamicAddressAT + 0x48), &colours, 4, NULL);
	ReadProcessMemory(hPro, (LPVOID)(dymnamicAddressAT + 0x4C), &purple, 4, NULL);
	ReadProcessMemory(hPro, (LPVOID)(dymnamicAddressAT + 0x50), &gold, 4, NULL);
    ReadProcessMemory(hPro, (LPVOID)(dymnamicAddressAT + 0x1D948), &z, 4, NULL);

	ui.addHealthATLineEdit->setText(QString::number(maximumHealth));
	ui.addQiATLineEdit->setText(QString::number(maximumSpirit));
	ui.healthATLineEdit->setText(QString::number(currentHealth));
	ui.qiATLineEdit->setText(QString::number(currentSpirit));
	ui.angryATLineEdit->setText(QString::number(currentQi));
	ui.experienceATLineEdit->setText(QString::number(experience));
	ui.gradeATLineEdit->setText(QString::number(currentGrade));
	ui.addGATKATLineEdit->setText(QString::number(attack));
	ui.addGDefenseATLineEdit->setText(QString::number(defense));
	ui.addQATKATLineEdit->setText(QString::number(spiritual));
	ui.addQDefenseATLineEdit->setText(QString::number(speed));
	ui.criticalATLineEdit->setText(QString::number(luck));

	ui.moneyATLineEdit->setText(QString::number(money));
	ui.blueATLineEdit->setText(QString::number(blue));
	ui.redATLineEdit->setText(QString::number(red));
	ui.greenATLineEdit->setText(QString::number(green));
	ui.coloursATLineEdit->setText(QString::number(colours));
	ui.purpleATLineEdit->setText(QString::number(purple));
	ui.goldATLineEdit->setText(QString::number(gold));
	ui.zATLineEdit->setText(QString::number(z));
}

//通过基址加偏移得到动态地址
UINT32 MemoryModifier::GetDymThroughBase(UINT32 baseAddress, UINT32 Offset[], UINT32 len)
{
	int Dym_temp;
	ReadProcessMemory(hPro, (LPVOID)baseAddress, &Dym_temp, 4, NULL);
	for (int i = 0; i < len; i++)
	{
		if (i == len - 1)
			Dym_temp += Offset[i];
		else
			ReadProcessMemory(hPro, (LPVOID)(Dym_temp + Offset[i]), &Dym_temp, 4, NULL);
	}
	return Dym_temp;
}
