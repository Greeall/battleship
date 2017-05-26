#pragma once
#include <stdlib.h> 
#include <ctime> 


const int INIT = 0;
const int ARRANGING = 1;
const int INTERMEDIATE_ARRANGING = 9;
const int PLAYING = 2;
const int END_GAME = 3;
const int ALL_SHIPS_EXIST = 4;
const int EMPTY_CELL = 1;
const int OCCUPIED_CELL = 0;
const int INJURED = 15;

const int CELL_NEAR_DECK = 2, MISS = 2;
const int CELL_NEAR_SET_SHIP = 22;
const int HUMAN_FIRST_STEP = 0;
const int AI_FIRST_STEP = 1;

namespace shipbattle {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			this->field = gcnew array<int, 2>(10, 10);
			this->field_for_ai_shoot = gcnew array<int, 2>(10, 10);
			this->field_pc = gcnew array<int, 2>(10, 10);
			this->array_for_random_choice = gcnew array<int>(100);
			this->limit_ships = 0;
			this->counter_killed_by_you_ships = 0;
			this->counter_killed_by_ai_ships = 0;
			this->counter_of_decks = 0;
			this->quantity_ships = 0;
			this->game_mode = ARRANGING;
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}



	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: static array<System::Windows::Forms::Button^>^buttons;
	private: static array<System::Windows::Forms::Button^>^pc_buttons;
	private: array<int, 2>^ field;
    private: bool is_game_over;
	private: array<int>^ array_for_random_choice; 
	private: array<int, 2>^ field_pc; 
	private: array<int, 2>^ field_for_ai_shoot; 
	private: int limit_ships;
	private: int quantity_ships;
	private: int counter_of_decks;
	private: int counter_killed_by_you_ships; 
	private: int counter_killed_by_ai_ships;
	private: int game_mode;
	private: int first_step;
	private: bool all_ships_exist;
	private: System::Windows::Forms::Label^  label1;








	protected: 

	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(45, 31);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(100, 23);
			this->button1->TabIndex = 3;
			this->button1->Text = L"Start game";
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
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(577, 473);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(0, 13);
			this->label3->TabIndex = 7;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(407, 473);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(35, 13);
			this->label1->TabIndex = 8;
			this->label1->Text = L"label1";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(838, 514);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: void make_free(array<System::Int32, 2> ^arr)
{
	for(int i=0; i<10; i++)
	{
		for(int j=0; j<10; j++)
		{
			arr[i,j] = EMPTY_CELL;
		}
	}
	limit_ships = 0;
}

private: void init_first_player()
{
	srand(time(NULL));
	first_step = rand() % 2;
}

private: void delete_old_field()
{
	for (int i = 0; i < 100; i++) 
	{
		this->Controls->Remove(this->buttons[i]); 
	}
}

private: void delete_old_pc_field()
{
	for (int i = 0; i < 100; i++) 
	{
		this->Controls->Remove(this->pc_buttons[i]); 
	}
}

private: void generation_field(System::Object^  sender, System::EventArgs^  e)
{
		this->buttons = gcnew array<System::Windows::Forms::Button^>(100); 
		for (int i = 0; i < 100; i++) 
		{ 
			int x = i % 10; 
			int y = i / 10; 
			this->buttons[i] = (gcnew System::Windows::Forms::Button()); 
			this->buttons[i]->Location = System::Drawing::Point(45 + x * 32, 126 + y * 30); 
			this->buttons[i]->Name = L"button" + i.ToString(); 
			this->buttons[i]->Size = System::Drawing::Size(29, 25); 
			this->buttons[i]->UseVisualStyleBackColor = true; 
			this->buttons[i]->Click += gcnew System::EventHandler(this, &MyForm::buttons_Click);
			this->Controls->Add(this->buttons[i]); 
		}
}

private: void generation_pc_field(System::Object^  sender, System::EventArgs^  e)
{
		this->pc_buttons = gcnew array<System::Windows::Forms::Button^>(100); 
		for (int i = 0; i < 100; i++) 
		{ 
			int x = i % 10; 
			int y = i / 10; 
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

private: void damaged_ship(array<System::Windows::Forms::Button^> ^arr, int i)
{
	arr[i]->Text = "O";
}

private: void sink_ship_full(array<System::Windows::Forms::Button^> ^arr, int i, int j)
{

	arr[i*10 + j]->Text = "X";
	
	//up
	if(i!=0)
		if(field_pc[i-1,j] == INJURED)
		{
			field_pc[i-1,j] = OCCUPIED_CELL;
			sink_ship_full(pc_buttons, i-1, j);
		}
		
	//down
	if(i!=10-1)
		if(field_pc[i+1,j] == INJURED)
		{
			field_pc[i+1,j] = OCCUPIED_CELL;
			sink_ship_full(pc_buttons, i+1, j);
		}
		
	//left
	if(j!=0)
		if(field_pc[i,j-1] == INJURED)
		{
			field_pc[i,j-1] = OCCUPIED_CELL;
			sink_ship_full(pc_buttons, i, j-1);
		}
		
	//right
	if(j!=10-1)
		if(field_pc[i,j+1] == INJURED)
		{
			field_pc[i,j+1] = OCCUPIED_CELL;
			sink_ship_full(pc_buttons, i, j+1);
		}
}

private: void past(array<System::Windows::Forms::Button^> ^arr, int i)
{
	arr[i]->Text = "-";
}

private: int i_index(int index_click_button)
{
	return index_click_button/10;
}

private: int j_index(int index_click_button)
{
	return index_click_button%10;
}

private: int convert_sender_to_index(System::Object^  sender)
{
	int index;
	for(int i=0; i<100; i++)
		if(pc_buttons[i] == sender)
			index = i;

	return index;
}

private: void make_10_to_22(array<System::Int32, 2> ^arr)
{
	for(int i = 0; i < 10; i++)
		for(int j = 0; j < 10; j++)
			if(arr[i,j] == 10)
				arr[i,j] = 2;

	for(int i = 0; i < 10; i++)
		for(int j = 0; j < 10; j++)
			if(arr[i,j] == 2)
				arr[i,j] = 22;
}


private: bool is_free_place_for_2deck_ship(array<System::Int32, 2> ^arr, int i, int j)
{
	bool answer = false;

	//up
	if(i!=0)
		if(arr[i-1,j] == EMPTY_CELL)
			answer = true;
			
	//down
	if(i!=10-1)
		if(arr[i+1,j] == EMPTY_CELL);
			answer = true;
			
	//left
	if(j!=0)
		if(arr[i,j-1] == EMPTY_CELL);
			answer = true;

	//right
	if(j!=10-1)
		if(arr[i,j+1] == EMPTY_CELL);
			answer = true;

	return answer;
}

private: bool is_free_place_for_3deck_ship(int index, array<System::Int32, 2> ^arr)
{
	//int index = convert_sender_to_index(sender);
	int i = i_index(index);
	int j = j_index(index);

	bool answer = false; 

	//up
	if(i!=0)
		if(arr[i-1,j] == EMPTY_CELL)
			if(is_free_place_for_2deck_ship(field, i-1, j))
					answer = true;
			
	//down
	if(i!=10-1)
		if(arr[i+1,j] == EMPTY_CELL)
			if(is_free_place_for_2deck_ship(field, i+1, j))
					answer = true;
			
	//left
	if(j!=0)
		if(arr[i,j-1] == EMPTY_CELL)
			if(is_free_place_for_2deck_ship(field, i, j-1))
					answer = true;
			
	//right
	if(j!=10-1)
		if(arr[i,j+1] == EMPTY_CELL)
			if(is_free_place_for_2deck_ship(field, i, j+1))
					answer = true;

	return answer;
}

private: void remove_access_to_area_about_ship(array<System::Int32, 2> ^arr, int i, int j)
{
	arr[i,j] = OCCUPIED_CELL;
	
	//up
	if(i!=0)
		if(arr[i-1,j] != OCCUPIED_CELL && arr[i-1,j] != CELL_NEAR_SET_SHIP && arr[i-1,j] != 10)
			arr[i-1,j] = CELL_NEAR_DECK;
		
	//down
	if(i!=10-1)
		if(arr[i+1,j] != OCCUPIED_CELL && arr[i+1,j] != CELL_NEAR_SET_SHIP && arr[i+1,j] != 10)
			arr[i+1,j] = CELL_NEAR_DECK;
		
	//left
	if(j!=0)
		if(arr[i,j-1] != OCCUPIED_CELL && arr[i,j-1] != CELL_NEAR_SET_SHIP && arr[i,j-1] != 10)
			arr[i,j-1] = CELL_NEAR_DECK;
		
	//right
	if(j!=10-1)
		if(arr[i,j+1] != OCCUPIED_CELL && arr[i,j+1] != CELL_NEAR_SET_SHIP && arr[i,j+1] != 10)
			arr[i,j+1] = CELL_NEAR_DECK;

	//up left
	if(i!=0 && j!=0)
		if(arr[i-1,j-1] != OCCUPIED_CELL && arr[i-1,j-1] != CELL_NEAR_SET_SHIP && arr[i-1,j-1] != 10)
			arr[i-1,j-1] = CELL_NEAR_DECK;

	//up right
	if(j!=10-1 && i!=0)
		if(arr[i-1,j+1] != OCCUPIED_CELL && arr[i-1,j+1] != CELL_NEAR_SET_SHIP && arr[i-1,j+1] != 10)
			arr[i-1,j+1] = CELL_NEAR_DECK;

	//down left
	if(i!=10-1 && j!=0)
		if(arr[i+1,j-1] != OCCUPIED_CELL && arr[i+1,j-1] != CELL_NEAR_SET_SHIP && arr[i+1,j-1] != 10)
			arr[i+1,j-1] = CELL_NEAR_DECK;

	//dow right
	if(i!=10-1 && j!=10-1)
		if(arr[i+1,j+1] != OCCUPIED_CELL && arr[i+1,j+1] != CELL_NEAR_SET_SHIP && arr[i+1,j+1] != 10)
			arr[i+1,j+1] = CELL_NEAR_DECK;

}

private: void place_for_additional_deck(array<System::Int32, 2> ^arr, int i, int j)
{
	arr[i,j] = OCCUPIED_CELL;
	
	//up
	if(i!=0)
		if(arr[i-1,j] != OCCUPIED_CELL && arr[i-1,j] != CELL_NEAR_SET_SHIP)
			arr[i-1,j] = 10;
		
	//down
	
	if(i!=10-1)
		if(arr[i+1,j] != OCCUPIED_CELL && arr[i+1,j] != CELL_NEAR_SET_SHIP)
			arr[i+1,j] = 10;
		
	//left
	if(j!=0)
		if(arr[i,j-1] != OCCUPIED_CELL && arr[i,j-1] != CELL_NEAR_SET_SHIP)
			arr[i,j-1] = 10;
		
	//right
	if(j!=10-1)
		if(arr[i,j+1] != OCCUPIED_CELL && arr[i,j+1] != CELL_NEAR_SET_SHIP)
			arr[i,j+1] = 10;

}

private: bool cell_is_empty(int index_click_button)
{
	int i = i_index(index_click_button);
	int j = j_index(index_click_button);
	return (field[i, j] == EMPTY_CELL);
}

private: void try_place_ship(System::Object^ sender)
{
	int index_click_button = convert_sender_to_index(sender);

	if(game_mode == ARRANGING)
	{
		if(cell_is_empty(index_click_button))
		{
			arrange_ship(buttons, index_click_button);
			remove_access_to_area_about_ship(field,i_index(index_click_button),j_index(index_click_button));
			counter_of_decks ++;
			place_for_additional_deck(field,i_index(index_click_button),j_index(index_click_button));
		}
	}	
}

private: void ai_make_shoot()
{
	int index;

	do
	{
		index = rand() % 100;
		if(field_for_ai_shoot[i_index(index), j_index(index)] == EMPTY_CELL)
		{
			if(field[i_index(index), j_index(index)] == OCCUPIED_CELL)
			{
				//проверить полнотью ли затоплен корабль
				//если не полностью, запомнить индекс, чтобы потом стрелять рядом
				//если полностью, то обозначить его полностью затопленным и обнулить индекс 

			}
			else
			{


			}
		}

	}while(field_for_ai_shoot[i_index(index), j_index(index)] != EMPTY_CELL);
	
	
}

private: void arrange_deck(int index)
{
	remove_access_to_area_about_ship(field_pc, i_index(index), j_index(index));
	arrange_ship(pc_buttons, index);
	place_for_additional_deck(field_pc, i_index(index), j_index(index));
}

private: void place_1deck_ships_randomly()
{
	
	int quantity_ai_ships = 4;
	do
	{
		int pc_index_ship = rand() % 100;

		if(field_pc[i_index(pc_index_ship), j_index(pc_index_ship)] == EMPTY_CELL)
		{
			remove_access_to_area_about_ship(field_pc,i_index(pc_index_ship),j_index(pc_index_ship));
			arrange_ship(pc_buttons, pc_index_ship);
			quantity_ai_ships--;
		}
	} while(quantity_ai_ships > 0);

	make_10_to_22(field_pc);
}

private: bool is_not_end_game()
{
	bool answer = true;

	if(counter_killed_by_ai_ships == 10)
	{
		label1->Text = "WIN AI";
		game_mode = END_GAME;
		answer = false;
	}

	if(counter_killed_by_you_ships == 10)
	{
		label1->Text = "WIN YOU";
		game_mode = END_GAME;
		answer = false;
	}

	return answer;
}

private: void place_4deck_ship_randomly()
{
	
	int counter_decks_of_4decks_ship = 0;
	int pc_index_ship = rand() % 100;

	arrange_deck(pc_index_ship);
		counter_decks_of_4decks_ship++;

		do
		{
			pc_index_ship = rand() % 100;
			if(field_pc[i_index(pc_index_ship), j_index(pc_index_ship)] == 10)
			{
				arrange_deck(pc_index_ship);
					counter_decks_of_4decks_ship++;
			}
		} while(counter_decks_of_4decks_ship < 4);

	make_10_to_22(field_pc);
}

private: void place_3deck_ships_randomly()
{
	int counter_of_ai_decks;
	int counter_of_3deck = 0;
	int pc_index_ship;

	do
	{
		counter_of_ai_decks = 1;
		pc_index_ship = rand() % 100;
		if(field_pc[i_index(pc_index_ship), j_index(pc_index_ship)] == EMPTY_CELL && is_free_place_for_3deck_ship(pc_index_ship, field_pc))
		{
			arrange_deck(pc_index_ship);
				do
				{
					pc_index_ship = rand() % 100;
					if(field_pc[i_index(pc_index_ship), j_index(pc_index_ship)] == 10)
					{
						arrange_deck(pc_index_ship);
						counter_of_ai_decks++;
					}
				} while(counter_of_ai_decks < 3);

			make_10_to_22(field_pc);
			counter_of_3deck++;
		}

	} while(counter_of_3deck < 2);

}

private: void place_2deck_ships_randomly()
{
	int counter_of_ai_decks;
	int counter_of_3deck = 0;
	int pc_index_ship;

	do
	{
		counter_of_ai_decks = 1;
		pc_index_ship = rand() % 100;
		if(field_pc[i_index(pc_index_ship), j_index(pc_index_ship)] == EMPTY_CELL && is_free_place_for_2deck_ship(field_pc, i_index(pc_index_ship), j_index(pc_index_ship)))
		{
			arrange_deck(pc_index_ship);
				do
				{
					pc_index_ship = rand() % 100;
					if(field_pc[i_index(pc_index_ship), j_index(pc_index_ship)] == 10)
					{
						arrange_deck(pc_index_ship);
						counter_of_ai_decks++;
					}
				} while(counter_of_ai_decks < 2);

			make_10_to_22(field_pc);
			counter_of_3deck++;
		}

	} while(counter_of_3deck < 3);
}
private: void place_ships_randomly()
{
	srand(time(NULL));
	place_4deck_ship_randomly();
	place_3deck_ships_randomly();
	place_2deck_ships_randomly();
	place_1deck_ships_randomly();
}

private: bool is_ship_sunken_full(array<System::Int32, 2> ^arr, int i, int j, array<bool, 2>^ visited)
{

	arr[i,j] = INJURED;

	bool full = true;

	if(visited == nullptr)
		visited = gcnew array<bool, 2>(10, 10); // array of cells which our recursive function already visited

	visited[i,j] = true; // set current cell as visited (our recursive func won visit it again)

	//up
	if(i!=0)
	{
		if(arr[i-1,j] == OCCUPIED_CELL)
			full = false;
		else if(arr[i-1,j] == INJURED && !visited[i-1,j]) // if cell is unjured AND we haven't visited it yet
			full = full && is_ship_sunken_full(field_pc, i-1, j, visited);
	}
		
	//down
	if(i!=10-1)
	{
		if(arr[i+1,j] == OCCUPIED_CELL)
			full = false;
		else if(arr[i+1,j] == INJURED && !visited[i+1,j]) // if cell is unjured AND we haven't visited it yet
			full = full && is_ship_sunken_full(field_pc, i+1, j, visited);
	}
		
	//left
	if(j!=0)
	{
		if(arr[i,j-1] == OCCUPIED_CELL)
			full = false;
		else if(arr[i,j-1] == INJURED && !visited[i,j-1]) // if cell is unjured AND we haven't visited it yet
			full = full && is_ship_sunken_full(field_pc, i, j-1, visited);
	}
		
	//right
	if(j!=10-1)
	{
		if(arr[i,j+1] == OCCUPIED_CELL)
			full = false;
		else if(arr[i,j+1] == INJURED && !visited[i,j+1]) // if cell is unjured AND we haven't visited it yet
			full = full && is_ship_sunken_full(field_pc, i, j+1, visited);
	}

	return full;
}

private: void try_shoot(System::Object^ sender)
{
	
	//if(game_mode == PLAYING)
	//{
		int index = convert_sender_to_index(sender);

		if(field_pc[i_index(index), j_index(index)] == OCCUPIED_CELL)
		{
			damaged_ship(pc_buttons,index);
			if(is_ship_sunken_full(field_pc,i_index(index),j_index(index), nullptr)) 
			{
				sink_ship_full(pc_buttons, i_index(index), j_index(index)); ///!!!!
				counter_killed_by_you_ships++;
			}
		}
		else
		{
			past(pc_buttons,index);
		}
	//}
	//else if(game_mode == ARRANGING)
	//{
	//	label3->Text = "Please, arrange all your ships!";
	//}
	
	if(is_not_end_game())
	{
		//ai_make_shoot();
	}
	
}


private: bool does_not_four_deck_ship_exist()
{
	return(quantity_ships == 0);
}
private: bool does_not_enough_three_deck_ships_exist()
{
	return(quantity_ships == 1 || quantity_ships == 2);
}
private: bool does_not_enough_two_deck_ships_exist()
{
	return(quantity_ships > 2 && quantity_ships < 6);
}
private: bool does_not_enough_one_deck_ships_exist()
{
	return(quantity_ships > 5 && quantity_ships < 10);
}

private: System::Void create_fields(System::Object^  sender, System::EventArgs^  e)
{
	generation_pc_field(sender,e);
	generation_field(sender,e);
	make_free(field);
	make_free(field_pc);
	place_ships_randomly();

}
private: void try_place_additional_deck(System::Object^  sender)
{
	int index_click_button = convert_sender_to_index(sender);

	if(game_mode == ARRANGING)
	{
		if(field[i_index(index_click_button),j_index(index_click_button)] == 10)
		{
			arrange_ship(buttons, index_click_button);
			remove_access_to_area_about_ship(field,i_index(index_click_button),j_index(index_click_button));
			counter_of_decks ++;
			place_for_additional_deck(field,i_index(index_click_button),j_index(index_click_button));
		}
	}	
}
private: void try_place_four_deck_ship(System::Object^  sender)
{	
	if(counter_of_decks == 0)
	{
		try_place_ship(sender);
	}
	else
	{
		try_place_additional_deck(sender);
	}

	if(counter_of_decks == 4)
	{
		make_10_to_22(field);
		counter_of_decks = 0;
		quantity_ships ++;
	}
}
private: void try_place_three_deck_ship(System::Object^  sender)
{
		int index = convert_sender_to_index(sender);

		if(counter_of_decks == 0)
		{
			if(is_free_place_for_3deck_ship(index, field))
				try_place_ship(sender);
		}
		else
		{
			try_place_additional_deck(sender);
		}

		if(counter_of_decks == 3)
		{
			make_10_to_22(field);
			counter_of_decks = 0;
			quantity_ships ++;
		}

}
private: void try_place_two_deck_ship(System::Object^  sender)
{
		int index = convert_sender_to_index(sender);
		int i = i_index(index);
		int j = j_index(index);

		if(counter_of_decks == 0)
		{
			if(is_free_place_for_2deck_ship(field, i, j))
				try_place_ship(sender);
		}
		else
		{
			try_place_additional_deck(sender);
		}

		if(counter_of_decks == 2)
		{
			make_10_to_22(field);
			counter_of_decks = 0;
			quantity_ships ++;
		}
}
private: void try_place_one_deck_ship(System::Object^  sender)
{
	try_place_ship(sender);

	if(counter_of_decks == 1)
	{
		counter_of_decks = 0;
		quantity_ships ++;
	}

	if(quantity_ships == 10)
		game_mode = PLAYING;
}


private: System::Void buttons_Click(System::Object^  sender, System::EventArgs^  e)
{	
		
	if(does_not_four_deck_ship_exist())
		try_place_four_deck_ship(sender);
	
	if(does_not_enough_three_deck_ships_exist())
		try_place_three_deck_ship(sender);

	if(does_not_enough_two_deck_ships_exist())
		try_place_two_deck_ship(sender);

	if(does_not_enough_one_deck_ships_exist())
		try_place_one_deck_ship(sender);

}

private: System::Void pc_buttons_Click(System::Object^  sender, System::EventArgs^  e)
{
	int i,index;

	for(int i = 0; i<100; i++)
	if(pc_buttons[i] == sender)
		index = i;

	//if(pc_buttons[index]->Text == "")
		try_shoot(sender);
}

};
}
