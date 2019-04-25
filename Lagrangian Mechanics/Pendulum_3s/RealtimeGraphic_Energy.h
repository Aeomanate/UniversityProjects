#pragma once
#include <vector>
#include "MyBool.h"
#include "PointsStorage.h"

namespace Pendulum_3s {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class RealtimeGraphic_Energy : public System::Windows::Forms::Form {
	public:
		RealtimeGraphic_Energy(MyBool^ isEnergyGraphicAlive, PointsStorage^ points)
		: isEnergyGraphicAlive(isEnergyGraphicAlive), points_storage(points) {
			InitializeComponent();
		}

	protected:
		~RealtimeGraphic_Energy() {
			if (components) delete components; 
			*isEnergyGraphicAlive = false;
		}
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  EnergyChart;
	private: System::Windows::Forms::Label^  label8;
	private: System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->EnergyChart = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->label8 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->EnergyChart))->BeginInit();
			this->SuspendLayout();
			// 
			// EnergyChart
			// 
			this->EnergyChart->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->EnergyChart->BorderlineColor = System::Drawing::Color::Transparent;
			this->EnergyChart->BorderlineDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Solid;
			chartArea1->Name = L"ChartArea1";
			this->EnergyChart->ChartAreas->Add(chartArea1);
			legend1->Name = L"Legend1";
			this->EnergyChart->Legends->Add(legend1);
			this->EnergyChart->Location = System::Drawing::Point(12, 36);
			this->EnergyChart->Name = L"EnergyChart";
			this->EnergyChart->Palette = System::Windows::Forms::DataVisualization::Charting::ChartColorPalette::None;
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series1->Color = System::Drawing::Color::Black;
			series1->Legend = L"Legend1";
			series1->MarkerSize = 1;
			series1->Name = L"Energy";
			series1->ShadowColor = System::Drawing::Color::Black;
			series1->XValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::Double;
			series1->YValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::Double;
			this->EnergyChart->Series->Add(series1);
			this->EnergyChart->Size = System::Drawing::Size(649, 304);
			this->EnergyChart->TabIndex = 1;
			this->EnergyChart->Text = L"Данные";
			// 
			// label8
			// 
			this->label8->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label8->Location = System::Drawing::Point(247, 9);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(169, 24);
			this->label8->TabIndex = 12;
			this->label8->Text = L"Энергия системы";
			// 
			// RealtimeGraphic_Energy
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(673, 352);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->EnergyChart);
			this->HelpButton = true;
			this->Name = L"RealtimeGraphic_Energy";
			this->Text = L" ";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->EnergyChart))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		MyBool^ isEnergyGraphicAlive;
		PointsStorage^ points_storage;



		void fill_EnergyChart() {
			size_t i = 0;
			for (auto point : points_storage->points)
				if(i++ % 30 == 0)
					EnergyChart->Series[0]->Points->AddXY(point.x, point.y);
		}
	public: void redraw_graphic() {
		EnergyChart->Series[0]->Points->Clear();
		fill_EnergyChart();
	}
	};
}
