#pragma once
#include <stdlib.h> 
#include <ctime> 
const int ARRANGING_SHIPS = 0;
const int PLAYING = 1;
const int EMPTY_CELL = 1;
const int OCCUPIED_CELL = 0;
const int CELL_NEAR_SHIP = 2, MISS = 2;
const int HUMAN_FIRST_STEP = 0;
const int AI_FIRST_STEP = 1;
const bool END_GAME = true;
const bool NOT_END_GAME = false;

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
			this->is_game_over = false;
			this->current_pc_height = 0;
			this->field = gcnew array<int, 2>(10, 10);
			this->field_for_ai_shoot = gcnew array<int, 2>(10, 10);
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
    private: bool is_game_over;
	private: array<int>^ array_for_random_choice; 
	private: array<int, 2>^ field_pc; 
	private: array<int, 2>^ field_for_ai_shoot; 
	private: int current_height;
	private: int current_pc_height;
	private: int limit_ships;
	private: int counter_killed_by_you_ships;
	private: int counter_killed_by_ai_ships;
	private: int game_mode;
	private: int first_step;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Label^  label3;







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
			this->label3 = (gcnew System::Windows::Forms::Label());
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
			this->button1->Size = System::Drawing::Size(100, 23);
			this->button1->TabIndex = 3;
			this->button1->Text = L"Create fields";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::create_fields);
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
			this->button2->Location = System::Drawing::Point(45, 463);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(100, 23);
			this->button2->TabIndex = 6;
			this->button2->Text = L"Start game";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::start_game);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(577, 473);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(35, 13);
			this->label3->TabIndex = 7;
			this->label3->Text = L"";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(838, 514);
			this->Controls->Add(this->label3);
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

private: void make_free(array<System::Int32, 2> ^arr)
{
	for(int i=0; i<current_height; i++)
	{
		for(int j=0; j<current_height; j++)
		{
			arr[i,j] = EMPTY_CELL;
		}
	}
	game_mode = ARRANGING_SHIPS;
	limit_ships = 0;
}

private: void init_first_player()
{
	srand(time(NULL));
	first_step = rand() % 2;
}

private: void delete_old_field(int current_height)
{
	for (int i = 0; i < current_height*current_height; i++) 
	{
		this->Controls->Remove(this->buttons[i]); 
	}
	current_pc_height = current_height;
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

private: void arrange_ship(array<System::Windows::Forms::Button^> ^arr, int i)
{
	arr[i]->Text = "+";
}

private: void sink_ship(array<System::Windows::Forms::Button^> ^arr, int i)
{
	arr[i]->Text = "X";
}

private: void past(array<System::Windows::Forms::Button^> ^arr, int i)
{
	arr[i]->Text = "-";
}

private: int i_index(int index_click_button)
{
	return index_click_button/current_height;
}

private: int j_index(int index_click_button)
{
	return index_click_button%current_height;
}

private: void remove_access_to_area_about_ship(array<System::Int32, 2> ^arr, int i, int j)
{
	arr[i,j] = OCCUPIED_CELL;
	
	//up
	if(i!=0)
		arr[i-1,j] = CELL_NEAR_SHIP;
		
	//down
	if(i!=current_height-1)
		arr[i+1,j] = CELL_NEAR_SHIP;
		
	//left
	if(j!=0)
		arr[i,j-1] = CELL_NEAR_SHIP;
		
	//right
	if(j!=current_height-1)
		arr[i,j+1] = CELL_NEAR_SHIP;

	//up left
	if(i!=0 && j!=0)
		arr[i-1,j-1] = CELL_NEAR_SHIP;

	//up right
	if(j!=current_height-1 && i!=0)
		arr[i-1,j+1] = CELL_NEAR_SHIP;

	//down left
	if(i!=current_height-1 && j!=0)
		arr[i+1,j-1] = CELL_NEAR_SHIP;

	//dow right
	if(i!=current_height-1 && j!=current_height-1)
		arr[i+1,j+1] = CELL_NEAR_SHIP;

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
	return max_ships;
}

private: bool cell_is_empty(int index_click_button)
{
	int i = i_index(index_click_button);
	int j = j_index(index_click_button);
	return (field[i, j] == EMPTY_CELL);
}

private: void try_place_ship(System::Object^ sender)
{
	label3->Text = "";
	int index_click_button;
	for(int i=0; i<current_height*current_height; i++)
	if(buttons[i] == sender)
		index_click_button = i;

	if(game_mode == ARRANGING_SHIPS)
	{
		if(cell_is_empty(index_click_button))
		{
			arrange_ship(buttons, index_click_button);
			limit_ships++;
			remove_access_to_area_about_ship(field,i_index(index_click_button),j_index(index_click_button));
			check_limit_ship();
		}
	}		
}

private: void ai_make_shoot()
{
	bool marker = 1;
	do
	{
		int index_ship = rand() % (current_height*current_height);

		if(field_for_ai_shoot[i_index(index_ship), j_index(index_ship)] == EMPTY_CELL)
		{
			if(field[i_index(index_ship), j_index(index_ship)] == OCCUPIED_CELL)
			{
				sink_ship(buttons,index_ship);
				counter_killed_by_ai_ships++;
				remove_access_to_area_about_ship(field_for_ai_shoot,i_index(index_ship),j_index(index_ship));				
			}
			else
			{
				past(buttons,index_ship);
				field_for_ai_shoot[i_index(index_ship),j_index(index_ship)] = MISS;
			}
			marker = 0;
		}
	}while(marker != 0);

	
}

private: void place_ships_randomly()
{
	
	for(int i=0; i<current_height*current_height; i++)
		array_for_random_choice[i] = i;
	srand(time(NULL));
	int quantity_ships = quantity_pc_ships(), pc_index_ship;
	do
	{
		pc_index_ship = rand() % (current_height*current_height);

		if(field_pc[i_index(pc_index_ship), j_index(pc_index_ship)] == EMPTY_CELL)
		{
			remove_access_to_area_about_ship(field_pc,i_index(pc_index_ship),j_index(pc_index_ship));
			quantity_ships--;
		}
	}while(quantity_ships > 0);
}

private: void stop_game()
{
	is_game_over = END_GAME;
}

private: void check_win()
{
	if ( counter_killed_by_ai_ships == quantity_pc_ships())
	{
		label3->Text = "WIN AI";
		stop_game();
	}
	else if(counter_killed_by_you_ships == quantity_pc_ships())
	{
		label3->Text = "WIN YOU";
		stop_game();
	}
}

private: void find_out_current_height()
{
	if(textBox1->Text == "")
		current_height = 2;
	else
	{
		current_height = Convert::ToInt32(textBox1->Text);
		if(current_height > 10)
			current_height = 10;
		else if(current_height == 0 || current_height == 1)
			current_height = 2;
	}
}


private: void try_shoot(System::Object^ sender)
{
	if(game_mode == PLAYING && is_game_over == NOT_END_GAME)
	{
		int index_click_button;
		for(int i=0; i<current_height*current_height; i++)
		{
			if(pc_buttons[i] == sender)
				index_click_button = i;
		}

		if(field_pc[i_index(index_click_button), j_index(index_click_button)] == OCCUPIED_CELL)
		{
			sink_ship(pc_buttons,index_click_button);
			counter_killed_by_you_ships++;
		}
		else
		{
			past(pc_buttons,index_click_button);
		}
		check_win();
		if(label3->Text == "")
		{
			ai_make_shoot();
			check_win();
		}
	}
}

private: System::Void create_fields(System::Object^  sender, System::EventArgs^  e)
{
	label3->Text = "";
	is_game_over = NOT_END_GAME;
	delete_old_field(current_height);
	find_out_current_height();
	delete_old_pc_field(current_pc_height);
	generation_pc_field(current_height,sender,e);
	make_free(field_pc);
	place_ships_randomly();
	generation_field(current_height,sender,e);
	make_free(field);	
}


private: System::Void buttons_Click(System::Object^  sender, System::EventArgs^  e)
{
	if(game_mode == ARRANGING_SHIPS)
		try_place_ship(sender);
}

private: System::Void pc_buttons_Click(System::Object^  sender, System::EventArgs^  e)
{
		try_shoot(sender);
}

private: System::Void start_game(System::Object^  sender, System::EventArgs^  e) 
{
	if(game_mode == PLAYING && is_game_over == NOT_END_GAME)
	{
		init_first_player();
		counter_killed_by_ai_ships = 0;
		counter_killed_by_you_ships = 0;
		is_game_over = NOT_END_GAME;
		make_free(field_for_ai_shoot);
		game_mode = PLAYING;

		if(first_step == AI_FIRST_STEP)
			ai_make_shoot();	
	}
	else if(game_mode == PLAYING && is_game_over == END_GAME)
	{
		label3->Text = "Click 'Create fields'";
	}
	else
	{
		label3->Text = "Please, arrange all your ships!";
	}
		
}
};
}
