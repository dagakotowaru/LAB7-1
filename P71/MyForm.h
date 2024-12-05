#pragma once
namespace P71 {
	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
		}
	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private:
		System::ComponentModel::Container^ components;
		System::Windows::Forms::PictureBox^ pictureBox;
		System::Windows::Forms::Button^ loadButton;
		System::Drawing::Bitmap^ bitmap;
#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->pictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->loadButton = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->BeginInit();
			this->SuspendLayout();
			//
			// pictureBox
			//
			this->pictureBox->Location = System::Drawing::Point(50, 12);
			this->pictureBox->Name = L"pictureBox";
			this->pictureBox->Size = System::Drawing::Size(470, 408);
			this->pictureBox->TabIndex = 0;
			this->pictureBox->TabStop = false;
			//
			// loadButton
			//
			this->loadButton->Location = System::Drawing::Point(51, 434);
			this->loadButton->Name = L"loadButton";
			this->loadButton->Size = System::Drawing::Size(153, 55);
			this->loadButton->TabIndex = 1;
			this->loadButton->Text = L"Загрузить изображение";
			this->loadButton->Click += gcnew System::EventHandler(this,
				&MyForm::DownloadPicture);
			//
			// MyForm
			//
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(578, 517);
			this->Controls->Add(this->pictureBox);
			this->Controls->Add(this->loadButton);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->EndInit();
			this->ResumeLayout(false);
		}
#pragma endregion
		void DownloadPicture(System::Object^ sender, System::EventArgs^ e)
		{
			OpenFileDialog^ dialog = gcnew OpenFileDialog();
			dialog->Filter = "Image files (*.jpg, *.jpeg, *.png)|*.jpg;*.jpeg;*.png";
			if (dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				bitmap = gcnew System::Drawing::Bitmap(dialog->FileName);
				pictureBox->Image = bitmap;
				int width = bitmap->Width;
				int height = bitmap->Height;
				MessageBox::Show("Width: " + width + ", Height: " + height, "Размеры изображения");
				Byte* red = new Byte[width];
				int row = 9;
				for (int x = 0; x < width; ++x)
				{
					red[x] = bitmap->GetPixel(x, row).R;
				}
				MessageBox::Show("RLE-сжатие десятой строки канала RED: " + RLECompress(red,
					width), "RLE-сжатие");
				delete[] red;
			}
		}
		String^ RLECompress(Byte* data, int length)
		{
			String^ comp = "";
			int count = 1;
			int limit = 10;
			int сount = 0;
			for (int i = 1; i < length; ++i)
			{
				if (data[i] == data[i - 1])
				{
					count++;
				}
				else
				{
					comp += data[i - 1] + "x" + count + " ";
					count = 1;
					count++;
					if (count >= limit)
					{
						comp += "\n";
						count = 0;
					}
				}
			}
			comp += data[length - 1] + "x" + count;
			return comp;
		}
	};
}