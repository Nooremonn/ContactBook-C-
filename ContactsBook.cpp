#include"ContactsBook.h"
#include<iostream>
#include<fstream>
#include"Address.h"


// default constructor
ContactsBook::ContactsBook()
{
	groups_list = nullptr;  contacts_list = nullptr;
	size_of_contacts = contacts_count = 0;
	size_of_group = 1;
	groups_list  = nullptr   /*= new Group[size_of_group]*/;
	groups_count = 0;
}

// parametrized Constructor
ContactsBook::ContactsBook(const int& contact_size)
{
	size_of_contacts = contact_size;
	contacts_count = 0;
	groups_count = 0;
	size_of_group = 1;
	groups_list = new Group[size_of_group + 1];
	contacts_list = new Contact[contact_size];
}

// function to create group list
void ContactsBook::CreateGroupList(const int& group_num)
{
	size_of_group = group_num;
	groups_list = new Group[size_of_group];
}

// function to add group in contacts_book
void ContactsBook::AddGroup(const Group& groups)
{
	groups_list[groups_count] = groups;
	groups_count++;
	ResizeGroupList();
	std::cout << "Group Added Sucessfully!" << std::endl;
}

// function to resize group list
void ContactsBook::ResizeGroupList()
{
	Group* new_list = new Group[size_of_group + 1];

	for (int i = 0; i < groups_count; i++)
		new_list[i] = groups_list[i];

	delete[] groups_list;
	groups_list = new_list;

	size_of_group++;
}

// function to add contact in contacts_list at respective index
void ContactsBook::AddContact(const Contact& contact)
{
	if (Full())
	{
		ResizeList();
	}
	contacts_list[contacts_count] = contact;
	contacts_count += 1;
}

// function to add contact in group
void ContactsBook::AddContactInGroup(const int& group_num, const int& contact_num)
{
	groups_list[group_num].AddMembers(contacts_list[contact_num].GetContactID());
}

// function to get contacts_count
int ContactsBook::TotalContact() const { return contacts_count; }

// function to get Total group
int ContactsBook::TotalGroups() const { return groups_count; }

// function to check if contacts_list is full or not
bool ContactsBook::Full()
{
	return contacts_count >= size_of_contacts;
}

// function to resize contacts_list if it was full 
void ContactsBook::ResizeList()
{

	Contact* new_temp = new Contact[size_of_contacts * 2];

	for (int i = 0; i < contacts_count; ++i) {
		new_temp[i] = contacts_list[i];
	}
	delete[] contacts_list;
	contacts_list = new_temp;
	size_of_contacts *= 2;
}

// function to sort contact list according to user choice i.e. first_name or last_name
void ContactsBook::SortContactsList(Contact*& contacts_list, std::string choice)
{
	std::string string_to_store_name;
	std::string string_to_store_name2;

	if (choice == "First Name")
	{
		for (int i = 0; i < contacts_count - 1; i++)
		{

			for (int j = 0; j < contacts_count - i -1; j++)
			{
				string_to_store_name = contacts_list[j].GetFirstName();
				string_to_store_name2 = contacts_list[j + 1].GetFirstName();
				if (string_to_store_name[0] > string_to_store_name2[0])
				{
					std::swap(contacts_list[j], contacts_list[j + 1]);
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < contacts_count - 1; i++)
		{
			string_to_store_name = contacts_list[i].GetLastName();

			for (int j = i + 1; j < contacts_count; j++)
			{
				string_to_store_name2 = contacts_list[j].GetLastName();
				if (string_to_store_name[0] > string_to_store_name2[0])
				{
					std::swap(contacts_list[i], contacts_list[j]);
				}
			}
		}
	}
}

// function to print contacts_id
void ContactsBook::PrintID() const
{
	for (int i = 0; i < contacts_count; i++) 
		std::cout << i + 1 << ". " << contacts_list[i].GetContactID() << std::endl;
}

// function to print group name
void ContactsBook::PrintGroupName() const
{
	for (int i = 0; i < groups_count; i++)
		std::cout << "Group " << i + 1 << ". " << groups_list[i].GetGroupname() << std::endl;

}

// function to check contact in group list
void ContactsBook::CheckContactInGroupList(const int& contact_num)
{
	string id = contacts_list[contact_num].GetContactID();

	for (int i = 0; i < groups_count; i++)
	{
		if (groups_list[i].CheckMember(id))
		{
			cout << groups_list[i].GetGroupname() << endl;
		}
	}

}

// function to print contacts
void ContactsBook::PrintContact(int num) const
{
	std::cout << "Contact is: " << contacts_list[num] << std::endl;
}

// function to update contact
void ContactsBook::UpdataContact(int contact_num)
{
	string previous_id = contacts_list[contact_num].GetContactID();
	std::cout << "Enter Following Details to update contact: " << std::endl;
	std::cin >> contacts_list[contact_num];
	std::cout << "Contact Updated Succesfully!" << std::endl;
	std::string new_id = contacts_list[contact_num].GetContactID();

	for (int i = 0; i < groups_count; i++)
	{
		groups_list[i].updateMember(previous_id, new_id);
	}
}

// function to delete contact detail
void ContactsBook::DeleteContact(int contact_num)
{
	std::string str = contacts_list[contact_num].GetContactID();

	contacts_list[contact_num] = Contact();
	for (int i = contact_num; i < contacts_count-1; i++)
	{
		if (contacts_list[i].Equals(Contact()))
			std::swap(contacts_list[i], contacts_list[i + 1]);
	}
	contacts_count -= 1;
	int member_num = -99;
	for (int i = 0; i < groups_count; i++)
	{
		groups_list[i].RemoveMember(member_num, str);
	}
}

// function to delete group form list
void ContactsBook::DeleteGroupFromList(const int& group_num)
{
	groups_list[group_num] = Group();
	for (int i = group_num; i < groups_count - 1; i++)
	{
		swap(groups_list[i], groups_list[i + 1]);
	}
	groups_count--;
}

// function to remove a contact from group
void ContactsBook::RemoveContactFromGroup(int& member_num, const int& group_num)
{
	groups_list[group_num].RemoveMember(member_num);
}

// function to get copy contacts_list
Contact* ContactsBook::GetCopy() const 
{
	Contact* new_contact_list = this->contacts_list;
	return new_contact_list; 
}

// function to get specific group
Group ContactsBook::GetGroup(int& group_num) const
{
	return groups_list[group_num];
}

// function to print sorted contact list
void ContactsBook::PrintContactSorted(const std::string& choice)
{

	Contact* new_contact_list = new Contact[contacts_count];

	// for loop to copy contacts in new_contact_list
	for (int i = 0; i < contacts_count; i++) new_contact_list[i] = *(contacts_list[i].CopyContact());

	SortContactsList(new_contact_list, choice);

	std::cout << "After Sorting Contact list is: " << std::endl;

	for (int i = 0; i < contacts_count; i++)
	{
		std::cout << "Contact NO. " << i + 1 << ": ";
		std::cout << new_contact_list[i] << std::endl;
	}
}

// function to merge duplicate contacts in list
void ContactsBook::MergeDuplicate() {
	int total_merged_count = 0;

	for (int i = 0; i < contacts_count - 1; i++)
	{
		for (int j = 0; j < contacts_count - 1; j++)
		{
			if ((contacts_list[j].Equals(contacts_list[j + 1])) )
			{
				std::cout << "Duplicate: ";
				std::cout << contacts_list[i] << std::endl;
				total_merged_count++;
				DeleteContact(j+1);
			}
		}
	}

	std::cout << "Total Merged Contacts: " << total_merged_count << std::endl;
}

// function to load data from file and to store in contacts_list
void ContactsBook::LoadFromFile(const std::string& file_name)
{
	std::ifstream read_file;
	read_file.open(file_name);

	if (read_file.is_open())
	{
		std::string read_data;
		int temp_size;
		// reading total contacts from file
		read_file >> temp_size;
		read_file >> std::ws;
		std::cout << "Total Contacts Readed: " << temp_size << std::endl;

		Contact* new_contacts_list = new Contact[temp_size];

		for (int i = 0; i < temp_size; i++)
		{
			std::getline(read_file, read_data, ',');     new_contacts_list[i].SetContactID(read_data);
			std::getline(read_file, read_data, ',');     new_contacts_list[i].SetFirstName(read_data);
			std::getline(read_file, read_data, ',');     new_contacts_list[i].SetLastName(read_data);
			std::getline(read_file, read_data, ',');     new_contacts_list[i].SetMobileNumber(read_data);
			std::getline(read_file, read_data, '\n');    new_contacts_list[i].SetEmailAddress(read_data);

			Address* new_temp_address = new Address();
			std::getline(read_file, read_data, ',');	new_temp_address->SetHouse(read_data);
			std::getline(read_file, read_data, ',');	new_temp_address->SetStreet(read_data);
			std::getline(read_file, read_data, ',');    new_temp_address->SetCity(read_data);
			std::getline(read_file, read_data, '\n');	new_temp_address->SetCountry(read_data);

			new_contacts_list[i].SetAddress(new_temp_address);

		}
		read_file.close();

		if (contacts_count == 0)
		{
			contacts_list = new_contacts_list;
			contacts_count += temp_size;
			size_of_contacts += temp_size;
		}
		else
		{
			for (int i = 0; i < temp_size; i++)
			{
				if (Full())
				{
					ResizeList();
				}
				contacts_list[contacts_count] = new_contacts_list[i];
				contacts_count++;
			}
		}
	}

	else
	{
		std::cout << "Error! in opening " << file_name << " \n";
	}
}

// function to load group data from file
void ContactsBook::LoadGroupFile(const std::string& file_name)
{
	ifstream load_file(file_name);
	if (load_file.is_open())
	{
		load_file >> groups_count;
		groups_list = new Group[groups_count];
		for (int i = 0; i < groups_count; i++)
		{
			groups_list[i].LoadFile(load_file);
		}
		size_of_group = groups_count;
		ResizeGroupList();
	}
	else
	{
		cout << "Error in Reading file for groups" << endl; 
		exit(1);
	}
}

// function to store data in file
void ContactsBook::SaveToFile(const std::string& file_name)
{
	std::ofstream save_file(file_name);

	if (save_file.is_open())
	{
		save_file << this->contacts_count << std::endl;                    // saving contacts_count to file

		for (int i = 0; i < contacts_count; i++)
		{
			save_file << contacts_list[i].GetContactID() << ","
				<< contacts_list[i].GetFirstName() << ","
				<< contacts_list[i].GetLastName() << ","
				<< contacts_list[i].GetMobileNumber() << ","
				<< contacts_list[i].GetEmailAddress() << "\n";
			Address new_temp_address = contacts_list[i].GetAddress();
			save_file << new_temp_address.GetHouse() << ","
				<< new_temp_address.GetStreet() << ","
				<< new_temp_address.GetCity() << ","
				<< new_temp_address.GetCountry() << "\n";
		}
		std::cout << "Conacts Saved!" << std::endl;
		save_file.close();
	}
	else
		std::cout << "Error! in saving data to " + file_name + " file." << std::endl;
}

// function to save group data in file
void ContactsBook::SaveGroupToFile(const std::string& file_name)
{
	ofstream write_file(file_name);
	if (write_file.is_open())
	{
		write_file << groups_count << endl;
		
		for (int i = 0; i < groups_count; i++)
		{
			groups_list[i].SaveToFile(write_file);
		}
	}
	else cout << "Cannot store Data to file" << endl;
}

// overloaded operator to print data on console
std::ostream& operator << (std::ostream& output, ContactsBook book)
{
	for (int i = 0; i < book.TotalContact(); i++) 
	{
		std::cout << "Contact No. " << i + 1 << ": ";
		std::cout << book.contacts_list[i];
	}
	return output;
}

// function to perform advance search 
void ContactsBook::AdvanceSearch(const std::string& string_to_search)
{
	bool found = false;
	std::string store_name;

	std::string str;

	std::cout << "Following Contacts Found in List: " << std::endl;
	for (int i = 0; i < contacts_count; i++)
	{
		str = contacts_list[i].GetFirstName() + contacts_list[i].GetContactID() + contacts_list[i].GetLastName() +
			contacts_list[i].GetEmailAddress() + contacts_list[i].GetMobileNumber();
		Address new_address = contacts_list[i].GetAddress();
		str += new_address.GetCity() + new_address.GetCountry() + new_address.GetHouse() + new_address.GetStreet();

		for (int j = 0; j < string_to_search.size(); j++)
		{
			for (int k = 0; k < str.length(); k++)
			{
				if(tolower(str[k]) == tolower(string_to_search[j]))
				{
					found = true;
					break;
				}
			}
		}
		if (found)
		{
			cout << contacts_list[i] << endl;
		}
	}
	if (!found)
	{
		cout << "No Data found!" << endl;
	}
}