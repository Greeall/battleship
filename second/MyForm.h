#pragma once
#include <stdlib.h> 

namespace shipbattle {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			this->current_height = 0;
			this->field = gcnew array<int, 2>(10, 10);
			this->limit_ships = 0;
			//this->field = gcnew array<int>;
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Label^  label2;
	private: static array<System::Windows::Forms::Button^>^buttons;
	private: array<int, 2>^ field; 
	private: int current_height;
	private: int limit_ships;
	



	protected: 

	private:
		/// <summary>
		/// “ребуетс€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ќб€зательный метод дл€ поддержки конструктора - не измен€йте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(45, 54);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 20);
			this->textBox1->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(42, 23);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(61, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Size of field";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(45, 89);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 3;
			this->button1->Text = L"Create field";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(45, 479);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(100, 23);
			this->button2->TabIndex = 4;
			this->button2->Text = L"Save your ships";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(68, 463);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(0, 13);
			this->label2->TabIndex = 5;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(838, 514);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: void delete_buttons(int size_field)
{
	for (int i = 0; i < size_field; i++) 
	{
		this->Controls->Remove(this->buttons[i]); 
	}

}

private: void generation_field(int height_field, System::Object^  sender, System::EventArgs^  e)
{
		this->buttons = gcnew array<System::Windows::Forms::Button^>(100); 
		for (int i = 0; i < height_field*height_field; i++) 
		{ 
			int x = i % height_field; 
			int y = i / height_field; 
			this->buttons[i] = (gcnew System::Windows::Forms::Button()); 
			this->buttons[i]->Location = System::Drawing::Point(45 + x * 32, 126 + y * 30); 
			this->buttons[i]->Name = L"button" + i.ToString(); 
			this->buttons[i]->Size = System::Drawing::Size(29, 25); 
			this->buttons[i]->UseVisualStyleBackColor = true; 
			this->buttons[i]->Click += gcnew System::EventHandler(this, &MyForm::buttons_Click);
			this->Controls->Add(this->buttons[i]); 
		}
}

private: int i_index(int index_click_button)
{
	return index_click_button/current_height;
}

private: int j_index(int index_click_button)
{
	return index_click_button%current_height;
}

private: void remove_access_to_area_about_ship(int i, int j)
{
	field[i,j] = 0;
	//up
	if(i!=0)
		field[i-1,j] = 0;
	//down
	if(i!=current_height-1)
		field[i+1,j] = 0;
	//left
	if(j!=0)
		field[i,j-1] = 0;
	//right
	if(j!=current_height-1)
		field[i,j+1] = 0;

	//up left
	if(i!=0 && j!=0)
		field[i-1,j-1] = 0;
	//up right
	if(j!=current_height-1 && i!=0)
		field[i-1,j+1] = 0;

	//down left
	if(i!=current_height-1 && j!=0)
		field[i+1,j-1] = 0;
	//dow right
	if(i!=current_height-1 && j!=current_height-1)
		field[i+1,j+1] = 0;

}

private: void check_limit_ship()
{
	int max_ships;
	switch(current_height)
	{
	case 2: max_ships = 1; break;
	case 3: max_ships = 2; break;
	case 4: max_ships = 3; break;
	case 5: max_ships = 5; break;
	case 6: max_ships = 7; break;
	case 7: max_ships = 8; break;
	case 8: max_ships = 10; break;
	case 9: max_ships = 12; break;
	case 10: max_ships = 14; break;
	}

	//if(limit_ships == max_ships) 
		//save_ships_on_field();
}

private: void try_select_ship(System::Object^ sender)
{
	//check_access_to_button();
	//select_ship();
	int index_click_button;
	for(int i=0; i<current_height*current_height; i++)
	if(buttons[i] == sender)
		index_click_button = i;
	buttons[index_click_button]->Text = "+";
	limit_ships++;
	remove_access_to_area_about_ship(i_index(index_click_button),j_index(index_click_button));
	check_limit_ship();
}

private: void make_free_field_in_array()
{
	for(int i=0; i<current_height; i++)
	{
		for(int j=0; j<current_height; j++)
		{
			field[i,j] = 1;
		}
	}
}

private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 delete_buttons(current_height*current_height);
			 current_height = Convert::ToInt32(textBox1->Text);
			 if(current_height > 10)
				 current_height = 10;
			 generation_field(current_height,sender,e);
			 make_free_field_in_array();

			
}

private: System::Void buttons_Click(System::Object^  sender, System::EventArgs^  e) {
			
			 try_select_ship(sender);
			// label2->Text = Convert::ToString(buttons[index_click_button]->Name);
			 
		 }

 private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) 
{
	
	 
}

};
}
