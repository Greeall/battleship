#pragma once
#include <stdlib.h> 
#include <ctime> 
const int ARRANGE_SHIPS = 0;
const int PLAYING = 1;
const int EMPTY_CELL = 1;
const int OCCUPIED_CELL = 0;

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
			this->current_pc_height = 0;
			this->field = gcnew array<int, 2>(10, 10);
			this->field_pc = gcnew array<int, 2>(10, 10);
			this->array_for_random_choice = gcnew array<int>(100);
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
	private: System::Windows::Forms::Label^  label2;
	private: static array<System::Windows::Forms::Button^>^buttons;
	private: static array<System::Windows::Forms::Button^>^pc_buttons;
	private: array<int, 2>^ field;
	private: array<int>^ array_for_random_choice; 
	private: array<int, 2>^ field_pc; 
	private: int current_height;
	private: int current_pc_height;
	private: int limit_ships;
	private: int occupied_cells;
	private: int game_mode;
	private: System::Windows::Forms::Button^  button2;




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
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
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
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(68, 463);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(0, 13);
			this->label2->TabIndex = 5;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(289, 479);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 6;
			this->button2->Text = L"Start game";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(838, 514);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: void delete_old_field(int current_height)
{
	for (int i = 0; i < current_height*current_height; i++) 
	{
		this->Controls->Remove(this->buttons[i]); 
	}

}

private: void delete_old_pc_field(int current_height)
{
	for (int i = 0; i < current_height*current_height; i++) 
	{
		this->Controls->Remove(this->pc_buttons[i]); 
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

private: void generation_pc_field(int height_field, System::Object^  sender, System::EventArgs^  e)
{
		this->pc_buttons = gcnew array<System::Windows::Forms::Button^>(100); 
		for (int i = 0; i < height_field*height_field; i++) 
		{ 
			int x = i % height_field; 
			int y = i / height_field; 
			this->pc_buttons[i] = (gcnew System::Windows::Forms::Button()); 
			this->pc_buttons[i]->Location = System::Drawing::Point(450 + x * 32, 126 + y * 30); 
			this->pc_buttons[i]->Name = L"button" + i.ToString(); 
			this->pc_buttons[i]->Size = System::Drawing::Size(29, 25); 
			this->pc_buttons[i]->UseVisualStyleBackColor = true; 
			this->pc_buttons[i]->Click += gcnew System::EventHandler(this, &MyForm::pc_buttons_Click);
			this->Controls->Add(this->pc_buttons[i]); 
		}

}

private: void arrange_ship(int i)
{
	buttons[i]->Text = "+";
}

private: void arrange_pc_ship(int i)
{
	pc_buttons[array_for_random_choice[i]]->Text = "+";
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
	field[i,j] = OCCUPIED_CELL;
	
	//up
	if(i!=0)
		field[i-1,j] = OCCUPIED_CELL;
		
	//down
	if(i!=current_height-1)
		field[i+1,j] = OCCUPIED_CELL;
		
	//left
	if(j!=0)
		field[i,j-1] = OCCUPIED_CELL;
		
	//right
	if(j!=current_height-1)
		field[i,j+1] = OCCUPIED_CELL;

	//up left
	if(i!=0 && j!=0)
		field[i-1,j-1] = OCCUPIED_CELL;

	//up right
	if(j!=current_height-1 && i!=0)
		field[i-1,j+1] = OCCUPIED_CELL;

	//down left
	if(i!=current_height-1 && j!=0)
		field[i+1,j-1] = OCCUPIED_CELL;

	//dow right
	if(i!=current_height-1 && j!=current_height-1)
		field[i+1,j+1] = OCCUPIED_CELL;

}

private: void check_limit_ship()
{
	int max_ships;
	switch(current_height)
	{
		case 2: max_ships = 1; break;
		case 3: max_ships = 1; break;
		case 4: max_ships = 3; break;
		case 5: max_ships = 4; break;
		case 6: max_ships = 6; break;
		case 7: max_ships = 8; break;
		case 8: max_ships = 10; break;
		case 9: max_ships = 12; break;
		case 10: max_ships = 15; break;
	}

	if(limit_ships == max_ships) 
		game_mode = PLAYING;
}

private: int quantity_pc_ships()
{
	int max_ships;
	switch(current_pc_height)
	{
		case 2: max_ships = 1; break;
		case 3: max_ships = 1; break;
		case 4: max_ships = 3; break;
		case 5: max_ships = 4; break;
		case 6: max_ships = 6; break;
		case 7: max_ships = 8; break;
		case 8: max_ships = 10; break;
		case 9: max_ships = 12; break;
		case 10: max_ships = 15; break;
	}
	return max_ships;
}

private: bool cell_is_empty(int index_click_button)
{
	int i = i_index(index_click_button);
	int j = j_index(index_click_button);
	return (field[i, j] == EMPTY_CELL);
}

private: void try_select_ship(System::Object^ sender)
{
	int index_click_button;
	for(int i=0; i<current_height*current_height; i++)
	if(buttons[i] == sender)
		index_click_button = i;

	if(game_mode == ARRANGE_SHIPS)
	{
		if(cell_is_empty(index_click_button))
		{
			arrange_ship(index_click_button);
			limit_ships++;
			remove_access_to_area_about_ship(i_index(index_click_button),j_index(index_click_button));
			check_limit_ship();
		}
	}
		
}
private: void swap(int i, int j)
{
	int buff = array_for_random_choice[i];
	array_for_random_choice[i] = array_for_random_choice[j];
	array_for_random_choice[j] = buff;
}

private: void remove_access_to_area_about_pc_ship(int pc_index_ship)
{
	//left
	if(pc_index_ship-1 >= 0 && pc_index_ship%current_pc_height != 0)
	{
		swap(pc_index_ship-1,current_height*current_height - occupied_cells - 1);
		occupied_cells++;
		//label2->Text = Convert::ToString(array_for_random_choice[4]);
	}

	//right
	if(pc_index_ship+1 < current_pc_height*current_pc_height && (pc_index_ship+1)%current_pc_height != 0)
	{
		swap(pc_index_ship+1,current_height*current_height - occupied_cells - 1);
		occupied_cells++;
		//label2->Text = Convert::ToString(array_for_random_choice[5]);
	}

	//down
	if(pc_index_ship+current_pc_height < current_pc_height*current_pc_height)
	{
		swap(pc_index_ship+current_pc_height,current_height*current_height - occupied_cells - 1);
		occupied_cells++;
		//label2->Text = Convert::ToString(array_for_random_choice[8]);
	}

	//up
	if(pc_index_ship-current_pc_height > current_pc_height-1)
	{
		swap(pc_index_ship-current_pc_height,current_height*current_height - occupied_cells - 1);
		occupied_cells++;
		//label2->Text = Convert::ToString(array_for_random_choice[8]);
	}

	//up left
	if(pc_index_ship%current_pc_height != 0 && pc_index_ship > current_pc_height-1)
	{
		swap(pc_index_ship-current_pc_height-1,current_height*current_height - occupied_cells - 1);
		occupied_cells++;
		//label2->Text = Convert::ToString(array_for_random_choice[8]);
	}
	
	//up right
	if((pc_index_ship+1)%current_pc_height != 0 && pc_index_ship > current_pc_height-1)
	{
		swap(pc_index_ship-current_pc_height+1,current_height*current_height - occupied_cells - 1);
		occupied_cells++;
		//label2->Text = Convert::ToString(array_for_random_choice[8]);
	}

	//down left
	if((pc_index_ship+1)%current_pc_height != 0 && pc_index_ship > current_pc_height-1)
	{
		swap(pc_index_ship-current_pc_height+1,current_height*current_height - occupied_cells - 1);
		occupied_cells++;
		//label2->Text = Convert::ToString(array_for_random_choice[8]);
	}

	//down right
}
private: void place_ships_randomly()
{
	for(int i=0; i<current_height*current_height; i++)
		array_for_random_choice[i] = i;
	srand(time(NULL));
	int quantity_ships = quantity_pc_ships(), pc_index_ship;
	occupied_cells = 0;
	for(int i=0; i<quantity_ships;i++)
	{
		pc_index_ship = rand() % (current_height*current_height - occupied_cells);
		//pc_index_ship = 4;
		arrange_pc_ship(pc_index_ship);
		swap(pc_index_ship,current_height*current_height - occupied_cells - 1);
		occupied_cells++;
		remove_access_to_area_about_pc_ship(pc_index_ship);
		//label2->Text = Convert::ToString(array_for_random_choice[4]);
	}

}

private: void make_free_field()
{
	for(int i=0; i<current_height; i++)
	{
		for(int j=0; j<current_height; j++)
		{
			field[i,j] = EMPTY_CELL;
		}
	}
}

private: void make_free_pc_field()
{
	for(int i=0; i<current_height; i++)
	{
		for(int j=0; j<current_height; j++)
		{
			field_pc[i,j] = EMPTY_CELL;
		}
	}
}

private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 delete_old_field(current_height);
			 current_height = Convert::ToInt32(textBox1->Text);
			 if(current_height > 10)
				 current_height = 10;
			 generation_field(current_height,sender,e);
			 make_free_field();
			 game_mode = ARRANGE_SHIPS;
			 limit_ships = 0;
}

private: System::Void buttons_Click(System::Object^  sender, System::EventArgs^  e)
{
	if(game_mode == ARRANGE_SHIPS)
		try_select_ship(sender);
}

private: System::Void pc_buttons_Click(System::Object^  sender, System::EventArgs^  e)
{
	
}

private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e)
{
	delete_old_pc_field(current_pc_height);
	current_pc_height = Convert::ToInt32(textBox1->Text);
	if(current_pc_height > 10)
		current_pc_height = 10;
	
	generation_pc_field(current_pc_height,sender,e);
	//make_free_pc_field();
	place_ships_randomly();
	//init_first_player();
}
};
}
