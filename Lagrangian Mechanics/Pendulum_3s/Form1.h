#pragma once
#include <cmath>
#include <time.h>
#include "RealtimeGraphic_Energy.h"
#include "RealtimeGraphic_Impulse.h"
#include <vector>
#include "MyBool.h"
#include "PointsStorage.h"

namespace CppCLR_WinformsProjekt {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace Pendulum_3s;

	public ref class Form1 : public System::Windows::Forms::Form {
	public:
		Form1(void) { InitializeComponent();  }
	protected:
		~Form1() { if (components)delete components; }
		System::Windows::Forms::PictureBox^  graphic;
		System::Windows::Forms::Button^  On;
		System::Windows::Forms::Label^  label9;
		System::Windows::Forms::Label^  label10;
		System::Windows::Forms::TrackBar^  TrackMidX;
		System::Windows::Forms::TrackBar^  TrackMidY;
		System::Windows::Forms::Label^  label11;
		System::Windows::Forms::Label^  label12;
		System::Windows::Forms::TextBox^  txtScaleX;
		System::Windows::Forms::TextBox^  txtScaleY;
	    System::Windows::Forms::TrackBar^  Track_b;
		System::Windows::Forms::Label^  label1;
	    System::Windows::Forms::TextBox^  Length_First;
		System::Windows::Forms::Label^  label2;
		System::Windows::Forms::Button^  Off;
	    System::Windows::Forms::Label^  label8;
	    System::Windows::Forms::TextBox^  Length_Second;
	    System::Windows::Forms::Label^  label13;
	    System::Windows::Forms::TrackBar^  Track_a;
	    System::Windows::Forms::Label^  label14;
	    System::Windows::Forms::Label^  label15;
	    System::Windows::Forms::TextBox^  Text_weight_1;
	    System::Windows::Forms::TextBox^  Text_weight_2;
	    System::Windows::Forms::Label^  label16;
	    System::Windows::Forms::Label^  label17;
	    System::Windows::Forms::Label^  label18;
	    System::Windows::Forms::TextBox^  Length_First_normal;
	    System::Windows::Forms::Label^  label20;
	    System::Windows::Forms::Label^  label21;
	    System::Windows::Forms::Label^  label22;
	    System::Windows::Forms::Label^  label19;
	    System::Windows::Forms::TextBox^  Speed_a;
	    System::Windows::Forms::TextBox^  Speed_b;
	    System::Windows::Forms::TextBox^  Speed_L;
	    System::Windows::Forms::Label^  label3;
	    System::Windows::Forms::TextBox^  Text_dt;
	    System::Windows::Forms::Label^  label4;
	    System::Windows::Forms::TextBox^  Text_k;
	    System::Windows::Forms::Label^  label5;
	    System::Windows::Forms::Label^  label6;
	    System::Windows::Forms::TextBox^  Text_EnergySystem;
	    System::Windows::Forms::TextBox^  Text_ImpulseSystem;
	    System::Windows::Forms::Label^  label7;
	    System::Windows::Forms::TextBox^  Text_CurTime;
	    System::Windows::Forms::TextBox^  Text_Gravity;
	    System::Windows::Forms::Label^  label23;
	private: System::Windows::Forms::CheckBox^  isDrawPendulum;
	protected:
		System::ComponentModel::Container ^components;
#pragma region Windows Form Designer generated code
		void InitializeComponent(void) {
			this->graphic = (gcnew System::Windows::Forms::PictureBox());
			this->On = (gcnew System::Windows::Forms::Button());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->TrackMidX = (gcnew System::Windows::Forms::TrackBar());
			this->TrackMidY = (gcnew System::Windows::Forms::TrackBar());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->txtScaleX = (gcnew System::Windows::Forms::TextBox());
			this->txtScaleY = (gcnew System::Windows::Forms::TextBox());
			this->Track_b = (gcnew System::Windows::Forms::TrackBar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->Length_First = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->Off = (gcnew System::Windows::Forms::Button());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->Length_Second = (gcnew System::Windows::Forms::TextBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->Track_a = (gcnew System::Windows::Forms::TrackBar());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->Text_weight_1 = (gcnew System::Windows::Forms::TextBox());
			this->Text_weight_2 = (gcnew System::Windows::Forms::TextBox());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->Length_First_normal = (gcnew System::Windows::Forms::TextBox());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->Speed_a = (gcnew System::Windows::Forms::TextBox());
			this->Speed_b = (gcnew System::Windows::Forms::TextBox());
			this->Speed_L = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->Text_dt = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->Text_k = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->Text_EnergySystem = (gcnew System::Windows::Forms::TextBox());
			this->Text_ImpulseSystem = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->Text_CurTime = (gcnew System::Windows::Forms::TextBox());
			this->Text_Gravity = (gcnew System::Windows::Forms::TextBox());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->isDrawPendulum = (gcnew System::Windows::Forms::CheckBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->graphic))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TrackMidX))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TrackMidY))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Track_b))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Track_a))->BeginInit();
			this->SuspendLayout();
			// 
			// graphic
			// 
			this->graphic->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->graphic->Location = System::Drawing::Point(9, 11);
			this->graphic->Name = L"graphic";
			this->graphic->Size = System::Drawing::Size(714, 456);
			this->graphic->TabIndex = 0;
			this->graphic->TabStop = false;
			this->graphic->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::graphic_Paint);
			// 
			// On
			// 
			this->On->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->On->Location = System::Drawing::Point(770, 11);
			this->On->Name = L"On";
			this->On->Size = System::Drawing::Size(49, 23);
			this->On->TabIndex = 1;
			this->On->Text = L"On";
			this->On->UseVisualStyleBackColor = true;
			this->On->Click += gcnew System::EventHandler(this, &Form1::B_F1_Click);
			// 
			// label9
			// 
			this->label9->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(788, 82);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(98, 13);
			this->label9->TabIndex = 2;
			this->label9->Text = L"Цетр координат X";
			// 
			// label10
			// 
			this->label10->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label10->AutoEllipsis = true;
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(928, 13);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(104, 13);
			this->label10->TabIndex = 2;
			this->label10->Text = L"Центр координат Y";
			this->label10->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// TrackMidX
			// 
			this->TrackMidX->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->TrackMidX->LargeChange = 1;
			this->TrackMidX->Location = System::Drawing::Point(770, 98);
			this->TrackMidX->Minimum = -10;
			this->TrackMidX->Name = L"TrackMidX";
			this->TrackMidX->Size = System::Drawing::Size(136, 45);
			this->TrackMidX->TabIndex = 5;
			this->TrackMidX->Scroll += gcnew System::EventHandler(this, &Form1::TrackMidX_Scroll);
			// 
			// TrackMidY
			// 
			this->TrackMidY->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->TrackMidY->LargeChange = 1;
			this->TrackMidY->Location = System::Drawing::Point(957, 37);
			this->TrackMidY->Minimum = -10;
			this->TrackMidY->Name = L"TrackMidY";
			this->TrackMidY->Orientation = System::Windows::Forms::Orientation::Vertical;
			this->TrackMidY->Size = System::Drawing::Size(45, 120);
			this->TrackMidY->TabIndex = 5;
			this->TrackMidY->Scroll += gcnew System::EventHandler(this, &Form1::TrackMidY_Scroll);
			// 
			// label11
			// 
			this->label11->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(767, 37);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(63, 13);
			this->label11->TabIndex = 2;
			this->label11->Text = L"Масштаб X";
			// 
			// label12
			// 
			this->label12->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(843, 38);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(63, 13);
			this->label12->TabIndex = 2;
			this->label12->Text = L"Масштаб Y";
			// 
			// txtScaleX
			// 
			this->txtScaleX->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->txtScaleX->Location = System::Drawing::Point(767, 54);
			this->txtScaleX->Name = L"txtScaleX";
			this->txtScaleX->Size = System::Drawing::Size(60, 20);
			this->txtScaleX->TabIndex = 3;
			this->txtScaleX->Text = L"45";
			this->txtScaleX->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// txtScaleY
			// 
			this->txtScaleY->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->txtScaleY->Location = System::Drawing::Point(843, 54);
			this->txtScaleY->Name = L"txtScaleY";
			this->txtScaleY->Size = System::Drawing::Size(60, 20);
			this->txtScaleY->TabIndex = 3;
			this->txtScaleY->Text = L"45";
			this->txtScaleY->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// Track_b
			// 
			this->Track_b->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->Track_b->LargeChange = 1;
			this->Track_b->Location = System::Drawing::Point(9, 532);
			this->Track_b->Maximum = 90;
			this->Track_b->Minimum = -90;
			this->Track_b->Name = L"Track_b";
			this->Track_b->Size = System::Drawing::Size(714, 45);
			this->Track_b->TabIndex = 1;
			this->Track_b->Value = -35;
			this->Track_b->Scroll += gcnew System::EventHandler(this, &Form1::Track_b_Scroll);
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(271, 554);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(199, 26);
			this->label1->TabIndex = 9;
			this->label1->Text = L"Начальное отклонение второго плеча\r\nв градусах: 0";
			this->label1->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// Length_First
			// 
			this->Length_First->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->Length_First->Location = System::Drawing::Point(741, 225);
			this->Length_First->Name = L"Length_First";
			this->Length_First->Size = System::Drawing::Size(88, 20);
			this->Length_First->TabIndex = 11;
			this->Length_First->Text = L"1";
			this->Length_First->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label2
			// 
			this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(744, 209);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(82, 13);
			this->label2->TabIndex = 10;
			this->label2->Text = L"Первого плеча";
			this->label2->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// Off
			// 
			this->Off->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->Off->Location = System::Drawing::Point(851, 11);
			this->Off->Name = L"Off";
			this->Off->Size = System::Drawing::Size(49, 23);
			this->Off->TabIndex = 17;
			this->Off->Text = L"Off";
			this->Off->UseVisualStyleBackColor = true;
			this->Off->Click += gcnew System::EventHandler(this, &Form1::Off_Click);
			// 
			// label8
			// 
			this->label8->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(846, 209);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(80, 13);
			this->label8->TabIndex = 10;
			this->label8->Text = L"Второго плеча";
			this->label8->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// Length_Second
			// 
			this->Length_Second->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->Length_Second->Location = System::Drawing::Point(842, 225);
			this->Length_Second->Name = L"Length_Second";
			this->Length_Second->Size = System::Drawing::Size(88, 20);
			this->Length_Second->TabIndex = 11;
			this->Length_Second->Text = L"0,5";
			this->Length_Second->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label13
			// 
			this->label13->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(816, 196);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(40, 13);
			this->label13->TabIndex = 10;
			this->label13->Text = L"Длина";
			this->label13->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// Track_a
			// 
			this->Track_a->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->Track_a->LargeChange = 1;
			this->Track_a->Location = System::Drawing::Point(12, 481);
			this->Track_a->Maximum = 90;
			this->Track_a->Minimum = -90;
			this->Track_a->Name = L"Track_a";
			this->Track_a->Size = System::Drawing::Size(714, 45);
			this->Track_a->TabIndex = 1;
			this->Track_a->Value = 48;
			this->Track_a->Scroll += gcnew System::EventHandler(this, &Form1::Track_a_Scroll);
			// 
			// label14
			// 
			this->label14->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(271, 503);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(200, 26);
			this->label14->TabIndex = 9;
			this->label14->Text = L"Начальное отклонение первого плеча\r\nв градусах: 0";
			this->label14->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// label15
			// 
			this->label15->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(816, 144);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(41, 13);
			this->label15->TabIndex = 12;
			this->label15->Text = L"Вес на";
			this->label15->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// Text_weight_1
			// 
			this->Text_weight_1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->Text_weight_1->Location = System::Drawing::Point(741, 173);
			this->Text_weight_1->Name = L"Text_weight_1";
			this->Text_weight_1->Size = System::Drawing::Size(88, 20);
			this->Text_weight_1->TabIndex = 11;
			this->Text_weight_1->Text = L"3";
			this->Text_weight_1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// Text_weight_2
			// 
			this->Text_weight_2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->Text_weight_2->Location = System::Drawing::Point(842, 173);
			this->Text_weight_2->Name = L"Text_weight_2";
			this->Text_weight_2->Size = System::Drawing::Size(88, 20);
			this->Text_weight_2->TabIndex = 11;
			this->Text_weight_2->Text = L"1";
			this->Text_weight_2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label16
			// 
			this->label16->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(747, 157);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(79, 13);
			this->label16->TabIndex = 10;
			this->label16->Text = L"Первом плече";
			this->label16->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// label17
			// 
			this->label17->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(849, 157);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(77, 13);
			this->label17->TabIndex = 10;
			this->label17->Text = L"Втором плече";
			this->label17->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// label18
			// 
			this->label18->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(751, 248);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(71, 13);
			this->label18->TabIndex = 10;
			this->label18->Text = L"Нормальная";
			this->label18->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// Length_First_normal
			// 
			this->Length_First_normal->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->Length_First_normal->Location = System::Drawing::Point(741, 264);
			this->Length_First_normal->Name = L"Length_First_normal";
			this->Length_First_normal->Size = System::Drawing::Size(88, 20);
			this->Length_First_normal->TabIndex = 11;
			this->Length_First_normal->Text = L"2";
			this->Length_First_normal->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label20
			// 
			this->label20->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label20->AutoSize = true;
			this->label20->Location = System::Drawing::Point(738, 333);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(126, 13);
			this->label20->TabIndex = 10;
			this->label20->Text = L"Угловая первого плеча";
			this->label20->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// label21
			// 
			this->label21->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label21->AutoSize = true;
			this->label21->Location = System::Drawing::Point(738, 360);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(125, 13);
			this->label21->TabIndex = 10;
			this->label21->Text = L"Угловая второго плеча";
			this->label21->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// label22
			// 
			this->label22->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label22->AutoSize = true;
			this->label22->Location = System::Drawing::Point(738, 381);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(145, 13);
			this->label22->TabIndex = 10;
			this->label22->Text = L"Растяжения первого плеча";
			this->label22->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// label19
			// 
			this->label19->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(846, 310);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(114, 13);
			this->label19->TabIndex = 12;
			this->label19->Text = L"Начальные скорости";
			this->label19->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// Speed_a
			// 
			this->Speed_a->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->Speed_a->Location = System::Drawing::Point(921, 326);
			this->Speed_a->Name = L"Speed_a";
			this->Speed_a->Size = System::Drawing::Size(88, 20);
			this->Speed_a->TabIndex = 11;
			this->Speed_a->Text = L"0";
			this->Speed_a->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// Speed_b
			// 
			this->Speed_b->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->Speed_b->Location = System::Drawing::Point(921, 353);
			this->Speed_b->Name = L"Speed_b";
			this->Speed_b->Size = System::Drawing::Size(88, 20);
			this->Speed_b->TabIndex = 11;
			this->Speed_b->Text = L"0";
			this->Speed_b->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// Speed_L
			// 
			this->Speed_L->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->Speed_L->Location = System::Drawing::Point(921, 378);
			this->Speed_L->Name = L"Speed_L";
			this->Speed_L->Size = System::Drawing::Size(88, 20);
			this->Speed_L->TabIndex = 11;
			this->Speed_L->Text = L"0";
			this->Speed_L->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label3
			// 
			this->label3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(738, 433);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(101, 13);
			this->label3->TabIndex = 12;
			this->label3->Text = L"Шаг по времени dt";
			this->label3->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// Text_dt
			// 
			this->Text_dt->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->Text_dt->Location = System::Drawing::Point(921, 430);
			this->Text_dt->Name = L"Text_dt";
			this->Text_dt->Size = System::Drawing::Size(88, 20);
			this->Text_dt->TabIndex = 11;
			this->Text_dt->Text = L"0,001";
			this->Text_dt->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label4
			// 
			this->label4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(755, 287);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(64, 13);
			this->label4->TabIndex = 10;
			this->label4->Text = L"Жёсткость";
			this->label4->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// Text_k
			// 
			this->Text_k->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->Text_k->Location = System::Drawing::Point(742, 303);
			this->Text_k->Name = L"Text_k";
			this->Text_k->Size = System::Drawing::Size(88, 20);
			this->Text_k->TabIndex = 11;
			this->Text_k->Text = L"35";
			this->Text_k->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label5
			// 
			this->label5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(764, 545);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(97, 13);
			this->label5->TabIndex = 12;
			this->label5->Text = L"Энергия системы";
			this->label5->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// label6
			// 
			this->label6->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(885, 545);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(147, 13);
			this->label6->TabIndex = 12;
			this->label6->Text = L"Момент импульса системы";
			this->label6->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// Text_EnergySystem
			// 
			this->Text_EnergySystem->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->Text_EnergySystem->Location = System::Drawing::Point(762, 560);
			this->Text_EnergySystem->Name = L"Text_EnergySystem";
			this->Text_EnergySystem->Size = System::Drawing::Size(99, 20);
			this->Text_EnergySystem->TabIndex = 11;
			this->Text_EnergySystem->Text = L"Hover mouse";
			this->Text_EnergySystem->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->Text_EnergySystem->MouseHover += gcnew System::EventHandler(this, &Form1::Text_EnergySystem_MouseHover);
			// 
			// Text_ImpulseSystem
			// 
			this->Text_ImpulseSystem->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->Text_ImpulseSystem->Location = System::Drawing::Point(914, 560);
			this->Text_ImpulseSystem->Name = L"Text_ImpulseSystem";
			this->Text_ImpulseSystem->Size = System::Drawing::Size(88, 20);
			this->Text_ImpulseSystem->TabIndex = 11;
			this->Text_ImpulseSystem->Text = L"Hover mouse";
			this->Text_ImpulseSystem->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->Text_ImpulseSystem->MouseHover += gcnew System::EventHandler(this, &Form1::Text_ImpulseSystem_MouseHover);
			// 
			// label7
			// 
			this->label7->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(830, 501);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(87, 13);
			this->label7->TabIndex = 12;
			this->label7->Text = L"Текущее время";
			this->label7->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// Text_CurTime
			// 
			this->Text_CurTime->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->Text_CurTime->Location = System::Drawing::Point(833, 517);
			this->Text_CurTime->Name = L"Text_CurTime";
			this->Text_CurTime->Size = System::Drawing::Size(84, 20);
			this->Text_CurTime->TabIndex = 11;
			this->Text_CurTime->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->Text_CurTime->MouseHover += gcnew System::EventHandler(this, &Form1::Text_EnergySystem_MouseHover);
			// 
			// Text_Gravity
			// 
			this->Text_Gravity->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->Text_Gravity->Location = System::Drawing::Point(921, 404);
			this->Text_Gravity->Name = L"Text_Gravity";
			this->Text_Gravity->Size = System::Drawing::Size(88, 20);
			this->Text_Gravity->TabIndex = 11;
			this->Text_Gravity->Text = L"9,81";
			this->Text_Gravity->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label23
			// 
			this->label23->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label23->AutoSize = true;
			this->label23->Location = System::Drawing::Point(738, 407);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(170, 13);
			this->label23->TabIndex = 12;
			this->label23->Text = L"Ускорение свободного падения";
			this->label23->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// isDrawPendulum
			// 
			this->isDrawPendulum->AutoSize = true;
			this->isDrawPendulum->Checked = true;
			this->isDrawPendulum->CheckState = System::Windows::Forms::CheckState::Checked;
			this->isDrawPendulum->Location = System::Drawing::Point(813, 481);
			this->isDrawPendulum->Name = L"isDrawPendulum";
			this->isDrawPendulum->Size = System::Drawing::Size(120, 17);
			this->isDrawPendulum->TabIndex = 18;
			this->isDrawPendulum->Text = L"Рисоать маятник\?";
			this->isDrawPendulum->UseVisualStyleBackColor = true;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1032, 589);
			this->Controls->Add(this->isDrawPendulum);
			this->Controls->Add(this->Off);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label23);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label19);
			this->Controls->Add(this->label15);
			this->Controls->Add(this->Text_weight_2);
			this->Controls->Add(this->Length_Second);
			this->Controls->Add(this->label13);
			this->Controls->Add(this->Speed_L);
			this->Controls->Add(this->Speed_b);
			this->Controls->Add(this->Speed_a);
			this->Controls->Add(this->Text_weight_1);
			this->Controls->Add(this->label17);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->Text_ImpulseSystem);
			this->Controls->Add(this->Text_CurTime);
			this->Controls->Add(this->Text_EnergySystem);
			this->Controls->Add(this->Text_Gravity);
			this->Controls->Add(this->Text_dt);
			this->Controls->Add(this->Text_k);
			this->Controls->Add(this->Length_First_normal);
			this->Controls->Add(this->Length_First);
			this->Controls->Add(this->label22);
			this->Controls->Add(this->label21);
			this->Controls->Add(this->label20);
			this->Controls->Add(this->label16);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label18);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label14);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->Track_a);
			this->Controls->Add(this->Track_b);
			this->Controls->Add(this->TrackMidY);
			this->Controls->Add(this->TrackMidX);
			this->Controls->Add(this->txtScaleY);
			this->Controls->Add(this->txtScaleX);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label12);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->On);
			this->Controls->Add(this->graphic);
			this->Name = L"Form1";
			this->Text = L"Pendulum 2";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->graphic))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TrackMidX))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TrackMidY))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Track_b))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Track_a))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		bool isOn;
		float x1, y1, x2, y2; // конца первого и второго плеча.
		float a_0, b_0, L_0, A_0, B_0, C_0, dt; // Начальные данные для решения диффура.
		float a_1, b_1, L_1, A_1, B_1, C_1, l, M, m, lambda, g, k; // Переменные на шаге n+1
		int maxX, maxY, midX, midY; // Центр координат. 
		float scaleX, scaleY = 50; // Масштаб осей 
		float biasMidX = 0, biasMidY = 0; // Смещение осей от центра координат
		float cur_time;

		RealtimeGraphic_Energy^ realtime_graphic_energy;
		MyBool^ isEnergyGraphicAlive;
		PointsStorage energy_in_time;

		RealtimeGraphic_Impulse^ realtime_graphic_impulse;
		MyBool^ isImpulseGraphicAlive;
		PointsStorage impulse_in_time;

		void initialize_params() {
			g = Convert::ToDouble(Text_Gravity->Text);
			isOn = false;
			maxY = this->graphic->Height, midY = maxY / 2 + biasMidY;
			maxX = this->graphic->Width, midX = maxX / 2 + biasMidX;
			scaleX = Convert::ToDouble(txtScaleX->Text);
			scaleY = Convert::ToDouble(txtScaleY->Text);

			a_0 = Track_a->Value * Math::PI / 180;
			b_0 = Track_b->Value * Math::PI / 180;
			L_0 = Convert::ToDouble(Length_First->Text);
			label14->Text = Convert::ToString("Начальное отклонение первого плеча\nв градусах: ") + Convert::ToString(Math::Round(a_0 * 180 / Math::PI));
			label1->Text = Convert::ToString("Начальное отклонение второго плеча\nв градусах: ") + Convert::ToString(Math::Round(b_0 * 180 / Math::PI));

			A_0 = Convert::ToDouble(Speed_a->Text);
			B_0 = Convert::ToDouble(Speed_b->Text);
			C_0 = Convert::ToDouble(Speed_L->Text);

			dt = Convert::ToDouble(Text_dt->Text);

			lambda = Convert::ToDouble(Length_First_normal->Text);
			l = Convert::ToDouble(Length_Second->Text);

			M = Convert::ToDouble(Text_weight_1->Text);
			m = Convert::ToDouble(Text_weight_2->Text);

			k = Convert::ToDouble(Text_k->Text);

			a_1 = 0;
			b_1 = 0;
			L_1 = 0;
				
			A_1 = 0;
			B_1 = 0;
			C_1 = 0;

			cur_time = 0;

			energy_in_time.points.clear();
			impulse_in_time.points.clear();
			isEnergyGraphicAlive = gcnew MyBool(false);
			isImpulseGraphicAlive = gcnew MyBool(false);
		}
		void B_F1_Click(System::Object^ sender, System::EventArgs^ e) {
			Off->Focus();
			initialize_params();
			isOn = true;
			while (isOn) {
				Application::DoEvents();
				show();
			}
		}
		void Off_Click(System::Object^  sender, System::EventArgs^ e) {
			isOn = false;
		}


		void evaluate_next_step() {
			A_1 = A_0 - dt*(l*m*sin(a_0 - b_0)*B_0*B_0 + g*m*sin(a_0) + 2 * C_0*M*A_0 + 2 * C_0*A_0*m + M*g*sin(a_0) + (k*m*cos(a_0 - b_0)*(L_0 - lambda)*(4 * M*sin(a_0 - b_0) - m*sin(3 * a_0 - 3 * b_0) + 3 * m*sin(a_0 - b_0))) / (2 * M*(2 * M + m - m*cos(2 * a_0 - 2 * b_0)))) / (L_0*(M + m));
			B_1 = B_0 + dt*(k*(L_0 - lambda)*(4 * M*sin(a_0 - b_0) - m*sin(3 * a_0 - 3 * b_0) + 3 * m*sin(a_0  - b_0))) / (2 * M*l*(2 * M + m - m*cos(2 * a_0  - 2 * b_0)));
			C_1 = C_0 + dt*(2 * L_0*M*M*A_0*A_0 + 2 * M*M*g*cos(a_0) - 2 * L_0*M*k - L_0*k*m + 2 * M*k*lambda + k*lambda*m + 2 * L_0*M*A_0*A_0*m + 2 * M*g*m*cos(a_0) + L_0*k*m*cos(2 * a_0 - 2 * b_0) - k*lambda*m*cos(2 * a_0 - 2 * b_0) + 2 * M*B_0*B_0*l*m*cos(a_0 - b_0)) / (2 * M*(M + m));
			a_1 = a_0 + dt*A_1;
			b_1 = b_0 + dt*B_1;
			L_1 = L_0 + dt*C_1;

			a_0 = a_1;
			b_0 = b_1;
			L_0 = L_1;
			A_0 = A_1;
			B_0 = B_1;
			C_0 = C_1;

			double T = 1.0 / 2 * ((M + m)*(C_0*C_0 + L_0*L_0*A_0*A_0) + B_0*B_0*l*l*m) + B_0*l*m*(C_0*sin(a_0 - b_0) + L_0*A_0*cos(a_0 - b_0));
			double U = -g*(M*L_0*cos(a_0) + m*(L_0*cos(a_0) + l*cos(b_0))) + k*(L_0 - lambda)*(L_0 - lambda) / 2;
			
			Text_EnergySystem->Text = Convert::ToString(T + U);
			size_t static limiter_energy_points = 0;
			if(limiter_energy_points++ % 10)
				energy_in_time.points.push_back({ cur_time, T + U });


			float M1 = M*((C_0*sin(a_0) + L_0*cos(a_0)*A_0)*L_0*cos(a_0) - L_0*sin(a_0)*(C_0*cos(a_0) - L_0*sin(a_0)*A_0));
			float M2 = m*((C_0*sin(a_0) + L_0*cos(a_0)*A_0 + l*cos(b_0)*B_0)*(L_0*cos(a_0) + l*cos(b_0)) - (L_0*sin(a_0) + l*sin(b_0))*(C_0*cos(a_0) - L_0*sin(a_0)*A_0 - l*sin(b_0)*B_0));
			float M_all = M1 + M2;
			Text_ImpulseSystem->Text = Convert::ToString(M_all);
			size_t static limiter_impulse_points = 0;
			if (limiter_impulse_points++ % 10)
				impulse_in_time.points.push_back({ cur_time, M_all });

			cur_time += dt;
		}
		void evaluate_xy() {
			x1 = L_0 * sin(a_0);
			y1 = L_0 * cos(a_0);
			x2 = x1 + l * sin(b_0);
			y2 = y1 + l * cos(b_0);
		}
		void show() {
			evaluate_next_step();

			evaluate_xy(); // Считаем положение концов маятника в декартовой системе. 
			Text_CurTime->Text = Convert::ToString(cur_time);

			if(isDrawPendulum->Checked) 
				graphic->Refresh();
			if (isEnergyGraphicAlive && abs(cur_time - int(cur_time)) < 0.01)
				realtime_graphic_energy->redraw_graphic();

			if (isImpulseGraphicAlive && abs(cur_time - int(cur_time)) < 0.01)
			realtime_graphic_impulse->redraw_graphic();;
		}
		void drawCircle(System::Windows::Forms::PaintEventArgs^  e, float x, float y) {
			float width, height;
			width = height = (scaleX + scaleY) * (Math::E * 2 / (scaleX + scaleY)) + 10;
			e->Graphics->FillEllipse(Brushes::Black,
				midX + x*scaleX - width / 2, midY - y*scaleY - height / 2,
				width, height);
		}
		void drawLine(System::Windows::Forms::PaintEventArgs^  e, float x1, float y1, float x2, float y2) {
			e->Graphics->DrawLine(Pens::Black,
				midX + x1*scaleX, midY - y1*scaleY,
				midX + x2*scaleX, midY - y2*scaleY);
		}
		void drawLineDotted(System::Windows::Forms::PaintEventArgs^  e, float x1, float y1, float x2, float y2) {
			Pen^ pen = gcnew Pen(Brushes::Gray, 0.05);
			pen->DashStyle::set(System::Drawing::Drawing2D::DashStyle::DashDotDot);
			e->Graphics->DrawLine(pen,
				midX + x1*scaleX, midY - y1*scaleY,
				midX + x2*scaleX, midY - y2*scaleY);
		}
		
		void graphic_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
			drawLine(e, 0, 0, x1, -y1);
			drawCircle(e, x1, -y1);
			drawLine(e, x1, -y1, x2, -y2);
			drawCircle(e, x2, -y2);

			setCoords(e);
		}
		void TrackMidX_Scroll(System::Object^  sender, System::EventArgs^  e) {
			biasMidX = TrackMidX->Value * 28;
			midX = maxX / 2 + biasMidX;
			graphic->Refresh();
		}
		void TrackMidY_Scroll(System::Object^  sender, System::EventArgs^  e) {
			biasMidY = -TrackMidY->Value * 22;
			midY = maxY / 2 + biasMidY;
			graphic->Refresh();
		}
		void Track_a_Scroll(System::Object^  sender, System::EventArgs^  e) {
			initialize_params();
			label14->Text = Convert::ToString("Начальное отклонение первого плеча\nв градусах: ") + Convert::ToString(Math::Round(a_0 * 180 / Math::PI));

			show();
		}
		void Track_b_Scroll(System::Object^  sender, System::EventArgs^  e) {
			initialize_params();
			label1->Text = Convert::ToString("Начальное отклонение второго плеча\nв градусах: ") + Convert::ToString(Math::Round(b_0 * 180 / Math::PI));

			show();
		}
		void setCoords(System::Windows::Forms::PaintEventArgs^  e) {
			drawLine(e, 0, -100, 0, 100); // Y
			drawLine(e, -100, 0, 100, 0); // X
										  // Стрелки Y
			e->Graphics->DrawLine(Pens::Black, midX, 0, midX - 4, 8);
			e->Graphics->DrawLine(Pens::Black, midX, 0, midX + 4, 8);
			// Стрелки X
			e->Graphics->DrawLine(Pens::Black, maxX, midY, maxX - 8, midY - 4);
			e->Graphics->DrawLine(Pens::Black, maxX, midY, maxX - 8, midY + 4);
			System::Drawing::Font^ font = gcnew System::Drawing::Font("Arial", 10);
			// Засечки X
			int negative = -1;
			int positive = 1;
			for (int i = midX - scaleX, j = midX + scaleX; i > 0 || j < maxX; i -= scaleX, j += scaleX) {
				e->Graphics->DrawLine(Pens::Black, i, midY - 4, i, midY + 4);
				e->Graphics->DrawString(Convert::ToString(negative--, 10), font, Brushes::Black, i - 9, midY + 4);
				e->Graphics->DrawLine(Pens::Black, j, midY - 4, j, midY + 4);
				e->Graphics->DrawString(Convert::ToString(positive++, 10), font, Brushes::Black, j - 6, midY + 4);
			}
			// Засечки Y
			negative = -1;
			positive = 1;
			for (int i = midY - scaleY, j = midY + scaleY; i > 0 || j < maxY; i -= scaleY, j += scaleY) {
				e->Graphics->DrawLine(Pens::Black, midX - 4, i, midX + 4, i);
				e->Graphics->DrawString(Convert::ToString(positive++, 10), font, Brushes::Black, midX + 4, i - 9);
				e->Graphics->DrawLine(Pens::Black, midX - 4, j, midX + 4, j);
				e->Graphics->DrawString(Convert::ToString(negative--, 10), font, Brushes::Black, midX + 4, j - 9);
			}
			// Названия осей
			e->Graphics->DrawString("y", font, Brushes::Black, midX + 5, 0);
			e->Graphics->DrawString("x", font, Brushes::Black, maxX - 10, midY - 25);
		}

		void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
			initialize_params();
			show();
		}

		void Text_EnergySystem_MouseHover(System::Object^  sender, System::EventArgs^  e) {
			if (!isEnergyGraphicAlive) {
				*isEnergyGraphicAlive = true;
				realtime_graphic_energy = gcnew RealtimeGraphic_Energy(isEnergyGraphicAlive, %energy_in_time);
			}
			realtime_graphic_energy->Show();
			realtime_graphic_energy->redraw_graphic();
		}
		void Text_ImpulseSystem_MouseHover(System::Object^  sender, System::EventArgs^  e) {
			if (!isImpulseGraphicAlive) {
				*isImpulseGraphicAlive = true;
				realtime_graphic_impulse = gcnew RealtimeGraphic_Impulse(isImpulseGraphicAlive, %impulse_in_time);
			}
			realtime_graphic_impulse->Show();
			realtime_graphic_impulse->redraw_graphic();
		}
};
}
