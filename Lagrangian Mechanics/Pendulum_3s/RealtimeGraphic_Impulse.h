#pragma once
#include "MyBool.h"
#include "PointsStorage.h"

namespace Pendulum_3s {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	public ref class RealtimeGraphic_Impulse : public System::Windows::Forms::Form {
	public: 
		RealtimeGraphic_Impulse(MyBool^ isEnergyGraphicAlive, PointsStorage^ points)
		: isEnergyGraphicAlive(isEnergyGraphicAlive), points_storage(points) { 
			InitializeComponent(); 
		}
	protected:
		~RealtimeGraphic_Impulse() { if (components) delete components; }

	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  ImpulseChart;
	private: System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void) {
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->ImpulseChart = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ImpulseChart))->BeginInit();
			this->SuspendLayout();
			// 
			// label8
			// 
			this->label8->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label8->Location = System::Drawing::Point(145, 0);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(244, 24);
			this->label8->TabIndex = 14;
			this->label8->Text = L"Момент имульса системы";
			// 
			// ImpulseChart
			// 
			this->ImpulseChart->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->ImpulseChart->BorderlineColor = System::Drawing::Color::Transparent;
			this->ImpulseChart->BorderlineDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Solid;
			chartArea1->Name = L"ChartArea1";
			this->ImpulseChart->ChartAreas->Add(chartArea1);
			legend1->Name = L"Legend1";
			this->ImpulseChart->Legends->Add(legend1);
			this->ImpulseChart->Location = System::Drawing::Point(12, 27);
			this->ImpulseChart->Name = L"ImpulseChart";
			this->ImpulseChart->Palette = System::Windows::Forms::DataVisualization::Charting::ChartColorPalette::None;
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series1->Color = System::Drawing::Color::Black;
			series1->Legend = L"Legend1";
			series1->MarkerSize = 1;
			series1->Name = L"Impulse";
			series1->ShadowColor = System::Drawing::Color::Black;
			series1->XValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::Double;
			series1->YValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::Double;
			this->ImpulseChart->Series->Add(series1);
			this->ImpulseChart->Size = System::Drawing::Size(512, 234);
			this->ImpulseChart->TabIndex = 13;
			this->ImpulseChart->Text = L"Данные";
			// 
			// RealtimeGraphic_Impulse
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(536, 273);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->ImpulseChart);
			this->Name = L"RealtimeGraphic_Impulse";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ImpulseChart))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		MyBool^ isEnergyGraphicAlive;
		PointsStorage^ points_storage;
	
		void fill_ImpulseChart() {
			size_t i = 0;
			for (auto point : points_storage->points)
				if (i++ % 30 == 0)
					ImpulseChart->Series[0]->Points->AddXY(point.x, point.y);
		}
	public: void redraw_graphic() {
		ImpulseChart->Series[0]->Points->Clear();
		fill_ImpulseChart();
	}
	};
}
