#pragma once
#include <Test.h>
#include <KCLists.hpp>

SCENARIO("KC::List<int> can be expanded and pulled from", "[List][int][List<int>][Data Structure]")
{
	GIVEN("A list that is initialized with nothing ")
	{
		KC::List<int> list;
		WHEN("nothing is added to the list")
		{
			THEN("the list has nothing inside of it")
			{
				REQUIRE(list.GetLength() == 0);
			}
			AND_THEN("the list's header is pointing to nothing")
			{
				REQUIRE(*list.GetHeader() == nullptr);
			}
		}

		KC::TraversalNode<int> currentHeader;

		AND_WHEN("one thing is added")
		{
			list.Push(1);
			currentHeader = list.GetHeader();

			THEN("the size changes")
			{
				REQUIRE(list.GetLength() == 1);
			}
			AND_THEN("the header is no longer null")
			{
				REQUIRE(*currentHeader != nullptr);
			}
			AND_WHEN("two things are added by array")
			{
				int arr[2] = { 2,3 };
				list.Push(2, arr);

				THEN("the size changes")
				{
					REQUIRE(list.GetLength() == 3);
				}
				AND_THEN("the header is not the old header")
				{
					REQUIRE(*list.GetHeader() != *currentHeader);
				}
				AND_THEN("the header points to the old header when increased by two")
				{
					REQUIRE(*(list.GetHeader() += 2) == *currentHeader);
				}

				currentHeader = list.GetHeader();

				AND_WHEN("three things are added by initializer list")
				{
					list.Push({ 4,5,6 });

					THEN("the size changes again")
					{
						REQUIRE(list.GetLength() == 6);
					}
					AND_THEN("the header is no longer the previous header")
					{
						REQUIRE(*list.GetHeader() != *currentHeader);
					}
					AND_THEN("the header points to the old header when increased by three")
					{
						REQUIRE(*(list.GetHeader() += 3) == *currentHeader);
					}

					currentHeader = list.GetHeader();

					AND_WHEN("a copy of the list is added to itself")
					{
						auto listCpy = list;
						list.Push(listCpy);

						THEN("the size doubles")
						{
							REQUIRE(list.GetLength() == 12);
						}
						AND_THEN("the header is no longer the previous header")
						{
							REQUIRE(*list.GetHeader() != *currentHeader);
						}
						AND_THEN("the header points to the old header when increased by six")
						{
							REQUIRE(*(list.GetHeader() += 6) == *currentHeader);
						}
						AND_THEN("the list is correct")
						{
							REQUIRE(list[0] == 4);
							REQUIRE(list[1] == 5);
							REQUIRE(list[2] == 6);
							REQUIRE(list[3] == 2);
							REQUIRE(list[4] == 3);
							REQUIRE(list[5] == 1);
							REQUIRE(list[6] == 4);
							REQUIRE(list[7] == 5);
							REQUIRE(list[8] == 6);
							REQUIRE(list[9] == 2);
							REQUIRE(list[10] == 3);
							REQUIRE(list[11] == 1);
						}
					}
					AND_WHEN("the list is added to itself")
					{
						list.Push(list);
						THEN("the size doubles")
						{
							REQUIRE(list.GetLength() == 12);
						}
						AND_THEN("the header is no longer the previous header")
						{
							REQUIRE(*list.GetHeader() != *currentHeader);
						}
						AND_THEN("the header points to the old header when increased by six")
						{
							REQUIRE(*(list.GetHeader() += 6) == *currentHeader);
						}
						AND_THEN("the list is correct")
						{
							REQUIRE(list[0] == 5);
							REQUIRE(list[1] == 5);
							REQUIRE(list[2] == 1);
							REQUIRE(list[3] == 5);
							REQUIRE(list[4] == 2);
							REQUIRE(list[5] == 1);
							REQUIRE(list[6] == 4);
							REQUIRE(list[7] == 5);
							REQUIRE(list[8] == 6);
							REQUIRE(list[9] == 2);
							REQUIRE(list[10] == 3);
							REQUIRE(list[11] == 1);
						}
					}
					AND_WHEN("one thing is pushed at a position greater than the length of the list")
					{
						THEN("throw an exception")
						{
							REQUIRE_THROWS([&]()
							{
								list.Push(100, 20);
							}());
						}
					}
					AND_WHEN("one thing is pushed at a position < 0")
					{
						THEN("throw an exception")
						{
							REQUIRE_THROWS([&]()
							{
								list.Push(100, -1);
							}());
						}
					}
					AND_WHEN("one thing is pushed at a valid position")
					{
						THEN("success")
						{
							list.Push(100, 3);
							REQUIRE(list[3] == 100);
						}
					}
				}
			}
		}
	}
	GIVEN("A list that is initialized with an array of 2 integers")
	{
		int arr[2] = { 10,9 };
		KC::List<int> list(2, arr);
		WHEN("nothing is done to it")
		{
			THEN("the length is correct")
			{
				REQUIRE(list.GetLength() == 2);
			}
			AND_THEN("the header points to nothing")
			{
				REQUIRE(*list.GetHeader() != nullptr);
			}
		}

		AND_WHEN("pulled from using a function")
		{
			auto headNode = list.GetHeader();
			auto a = list.Pull();

			THEN("the data is correctly pulled")
			{
				REQUIRE(a == 10);
			}
			AND_THEN("the list is resized acccordingly")
			{
				REQUIRE(list.GetLength() == 1);
			}
		}

		AND_WHEN("pulled from using operators")
		{
			auto headNode = list.GetHeader();
			int a;
			list >> a;

			THEN("the data is correctly pulled")
			{
				REQUIRE(a == 10);
			}
			AND_THEN("the list is resized acccordingly")
			{
				REQUIRE(list.GetLength() == 1);
			}
		}
		AND_WHEN("pulled from multiple times using operators")
		{
			auto headNode = list.GetHeader();
			int a, b;
			list >> a >> b;

			THEN("the data is correctly pulled")
			{
				REQUIRE(a == 10);
				REQUIRE(b == 9);
			}
			AND_THEN("the list is resized acccordingly")
			{
				REQUIRE(list.GetLength() == 0);
			}
			AND_THEN("the list's header is now a nullptr")
			{
				REQUIRE(*list.GetHeader() == nullptr);
			}
		}
		AND_WHEN("accessing an index larger than the length of the list")
		{
			THEN("throws an exception")
			{
				REQUIRE_THROWS([&]()
				{
					auto a = list[2];
				}());
			}
		}
		AND_WHEN("accessing a negative index")
		{
			THEN("throws an exception")
			{
				REQUIRE_THROWS([&]()
				{
					auto a = list[-1];
				}());
			}
		}
	}
	GIVEN("A list is initialized with an initializer_list of 3 integers")
	{
		KC::List<int> list({ 100,10,1 });
		WHEN("nothing is done")
		{
			THEN("the list has the correct length")
			{
				REQUIRE(list.GetLength() == 3);
			}
			AND_THEN("the list's header exists")
			{
				REQUIRE(*list.GetHeader() != nullptr);
			}
			AND_THEN("the list is correct")
			{
				REQUIRE(list[0] == 100);
				REQUIRE(list[1] == 10);
				REQUIRE(list[2] == 1);
			}
		}
		AND_WHEN("an integer is added with an operator")
		{
			auto header = list.GetHeader();
			list << 5;
			THEN("the list has the correct length")
			{
				REQUIRE(list.GetLength() == 4);
			}
			AND_THEN("the list's header does not equal the previous header")
			{
				REQUIRE(*list.GetHeader() != *header);
			}
			AND_THEN("the list's header + 1 is equal to the previous header")
			{
				REQUIRE(*(list.GetHeader() + 1) == *header);
			}
		}
	}
}
SCENARIO("KC::List<char> can be expanded and pulled from", "[List][char][List<char>][Data Structure]")
{
	GIVEN("A list that is initialized with nothing ")
	{
		KC::List<char> list;
		WHEN("nothing is added to the list")
		{
			THEN("the list has nothing inside of it")
			{
				REQUIRE(list.GetLength() == 0);
			}
			AND_THEN("the list's header is pointing to nothing")
			{
				REQUIRE(*list.GetHeader() == nullptr);
			}
		}

		KC::TraversalNode<char> currentHeader;

		AND_WHEN("one thing is pushed")
		{
			list.Push('a');
			currentHeader = list.GetHeader();

			THEN("the size changes")
			{
				REQUIRE(list.GetLength() == 1);
			}
			AND_THEN("the header is no longer null")
			{
				REQUIRE(*currentHeader != nullptr);
			}
			AND_WHEN("two things are pushed by array")
			{
				char arr[2] = { 'b','c' };
				list.Push(2, arr);

				THEN("the size changes")
				{
					REQUIRE(list.GetLength() == 3);
				}
				AND_THEN("the header is not the old header")
				{
					REQUIRE(*list.GetHeader() != *currentHeader);
				}
				AND_THEN("the header points to the old header when increased by two")
				{
					REQUIRE(*(list.GetHeader() += 2) == *currentHeader);
				}

				currentHeader = list.GetHeader();

				AND_WHEN("three things are pushed by initializer list")
				{
					list.Push({ 'd','e','f' });

					THEN("the size changes again")
					{
						REQUIRE(list.GetLength() == 6);
					}
					AND_THEN("the header is no longer the previous header")
					{
						REQUIRE(*list.GetHeader() != *currentHeader);
					}
					AND_THEN("the header points to the old header when increased by three")
					{
						REQUIRE(*(list.GetHeader() += 3) == *currentHeader);
					}

					currentHeader = list.GetHeader();

					AND_WHEN("a copy of the list is pushed to itself")
					{
						auto listCpy = list;
						list.Push(listCpy);

						THEN("the size doubles")
						{
							REQUIRE(list.GetLength() == 12);
						}
						AND_THEN("the header is no longer the previous header")
						{
							REQUIRE(*list.GetHeader() != *currentHeader);
						}
						AND_THEN("the header points to the old header when increased by six")
						{
							REQUIRE(*(list.GetHeader() += 6) == *currentHeader);
						}
						AND_THEN("the list is correct")
						{
							REQUIRE(list[0] == 'd');
							REQUIRE(list[1] == 'e');
							REQUIRE(list[2] == 'f');
							REQUIRE(list[3] == 'b');
							REQUIRE(list[4] == 'c');
							REQUIRE(list[5] == 'a');
							REQUIRE(list[6] == 'd');
							REQUIRE(list[7] == 'e');
							REQUIRE(list[8] == 'f');
							REQUIRE(list[9] == 'b');
							REQUIRE(list[10] == 'c');
							REQUIRE(list[11] == 'a');
						}
					}
					AND_WHEN("the list is pushed to itself")
					{
						list.Push(list);
						THEN("the size doubles")
						{
							REQUIRE(list.GetLength() == 12);
						}
						AND_THEN("the header is no longer the previous header")
						{
							REQUIRE(*list.GetHeader() != *currentHeader);
						}
						AND_THEN("the header points to the old header when increased by six")
						{
							REQUIRE(*(list.GetHeader() += 6) == *currentHeader);
						}
						AND_THEN("the list is correct")
						{
							REQUIRE(list[0] == 'e');
							REQUIRE(list[1] == 'e');
							REQUIRE(list[2] == 'a');
							REQUIRE(list[3] == 'e');
							REQUIRE(list[4] == 'b');
							REQUIRE(list[5] == 'a');
							REQUIRE(list[6] == 'd');
							REQUIRE(list[7] == 'e');
							REQUIRE(list[8] == 'f');
							REQUIRE(list[9] == 'b');
							REQUIRE(list[10] == 'c');
							REQUIRE(list[11] == 'a');
						}
					}
					AND_WHEN("one thing is pushed at a position greater than the length of the list")
					{
						THEN("throw an exception")
						{
							REQUIRE_THROWS([&]()
							{
								list.Push('a', 20);
							}());
						}
					}
					AND_WHEN("one thing is pushed at a position < 0")
					{
						THEN("throw an exception")
						{
							REQUIRE_THROWS([&]()
							{
								list.Push('a', -1);
							}());
						}
					}
					AND_WHEN("one thing is pushed at a valid position")
					{
						THEN("success")
						{
							list.Push('a', 3);
							REQUIRE(list[3] == 'a');
						}
					}
				}
			}
		}
	}
	GIVEN("A list that is initialized with an array of 2 characters")
	{
		char arr[2] = { 'a','b' };
		KC::List<char> list(2, arr);
		WHEN("nothing is done to it")
		{
			THEN("the length is correct")
			{
				REQUIRE(list.GetLength() == 2);
			}
			AND_THEN("the header points to nothing")
			{
				REQUIRE(*list.GetHeader() != nullptr);
			}
		}

		AND_WHEN("pulled from using a function")
		{
			auto headNode = list.GetHeader();
			auto a = list.Pull();

			THEN("the data is correctly pulled")
			{
				REQUIRE(a == 'a');
			}
			AND_THEN("the list is resized acccordingly")
			{
				REQUIRE(list.GetLength() == 1);
			}
		}

		AND_WHEN("pulled from using operators")
		{
			auto headNode = list.GetHeader();
			char a;
			list >> a;

			THEN("the data is correctly pulled")
			{
				REQUIRE(a == 'a');
			}
			AND_THEN("the list is resized acccordingly")
			{
				REQUIRE(list.GetLength() == 1);
			}
		}
		AND_WHEN("pulled from multiple times using operators")
		{
			auto headNode = list.GetHeader();
			char a, b;
			list >> a >> b;

			THEN("the data is correctly pulled")
			{
				REQUIRE(a == 'a');
				REQUIRE(b == 'b');
			}
			AND_THEN("the list is resized acccordingly")
			{
				REQUIRE(list.GetLength() == 0);
			}
			AND_THEN("the list's header is now a nullptr")
			{
				REQUIRE(*list.GetHeader() == nullptr);
			}
		}
		AND_WHEN("accessing an index larger than the length of the list")
		{
			THEN("throws an exception")
			{
				REQUIRE_THROWS([&]()
				{
					auto a = list[2];
				}());
			}
		}
		AND_WHEN("accessing a negative index")
		{
			THEN("throws an exception")
			{
				REQUIRE_THROWS([&]()
				{
					auto a = list[-1];
				}());
			}
		}
	}
	GIVEN("A list is initialized with an initializer_list of 3 characters")
	{
		KC::List<char> list({ 'x','y','z' });
		WHEN("nothing is done")
		{
			THEN("the list has the correct length")
			{
				REQUIRE(list.GetLength() == 3);
			}
			AND_THEN("the list's header exists")
			{
				REQUIRE(*list.GetHeader() != nullptr);
			}
			AND_THEN("the list is correct")
			{
				REQUIRE(list[0] == 'x');
				REQUIRE(list[1] == 'y');
				REQUIRE(list[2] == 'z');
			}
		}
		AND_WHEN("an integer is added with an operator")
		{
			auto header = list.GetHeader();
			list << 'a';
			THEN("the list has the correct length")
			{
				REQUIRE(list.GetLength() == 4);
			}
			AND_THEN("the list's header does not equal the previous header")
			{
				REQUIRE(*list.GetHeader() != *header);
			}
			AND_THEN("the list's header + 1 is equal to the previous header")
			{
				REQUIRE(*(list.GetHeader() + 1) == *header);
			}
		}
	}
}
SCENARIO("KC::LinkedList<int> is an expanded version of KC::List<int>", "[LinkedList][int][LinkedList<int>][List][List<int>][Data Structure][Derived]")
{
	GIVEN("A list that is initialized with nothing ")
	{
		KC::LinkedList<int> list;
		WHEN("nothing is added to the list")
		{
			THEN("the list has nothing inside of it")
			{
				REQUIRE(list.GetLength() == 0);
			}
			AND_THEN("the list's header is pointing to nothing")
			{
				REQUIRE(*list.GetHeader() == nullptr);
			}
		}

		KC::TraversalNode<int> currentHeader;

		AND_WHEN("one thing is pushed")
		{
			list.Push(1);
			currentHeader = list.GetHeader();

			THEN("the size changes")
			{
				REQUIRE(list.GetLength() == 1);
			}
			AND_THEN("the header is no longer null")
			{
				REQUIRE(*currentHeader != nullptr);
			}
			AND_WHEN("two things are pushed by array")
			{
				int arr[2] = { 2,3 };
				list.Push(2, arr);

				THEN("the size changes")
				{
					REQUIRE(list.GetLength() == 3);
				}
				AND_THEN("the header is not the old header")
				{
					REQUIRE(*list.GetHeader() != *currentHeader);
				}
				AND_THEN("the header points to the old header when increased by two")
				{
					REQUIRE(*(list.GetHeader() += 2) == *currentHeader);
				}

				currentHeader = list.GetHeader();

				AND_WHEN("three things are pushed by initializer list")
				{
					list.Push({ 4,5,6 });

					THEN("the size changes again")
					{
						REQUIRE(list.GetLength() == 6);
					}
					AND_THEN("the header is no longer the previous header")
					{
						REQUIRE(*list.GetHeader() != *currentHeader);
					}
					AND_THEN("the header points to the old header when increased by three")
					{
						REQUIRE(*(list.GetHeader() += 3) == *currentHeader);
					}

					currentHeader = list.GetHeader();

					AND_WHEN("a copy of the list is pushed to itself")
					{
						auto listCpy = list;
						list.Push(listCpy);

						THEN("the size doubles")
						{
							REQUIRE(list.GetLength() == 12);
						}
						AND_THEN("the header is no longer the previous header")
						{
							REQUIRE(*list.GetHeader() != *currentHeader);
						}
						AND_THEN("the header points to the old header when increased by six")
						{
							REQUIRE(*(list.GetHeader() += 6) == *currentHeader);
						}
						AND_THEN("the list is correct")
						{
							REQUIRE(list[0] == 4);
							REQUIRE(list[1] == 5);
							REQUIRE(list[2] == 6);
							REQUIRE(list[3] == 2);
							REQUIRE(list[4] == 3);
							REQUIRE(list[5] == 1);
							REQUIRE(list[6] == 4);
							REQUIRE(list[7] == 5);
							REQUIRE(list[8] == 6);
							REQUIRE(list[9] == 2);
							REQUIRE(list[10] == 3);
							REQUIRE(list[11] == 1);
						}
					}
					AND_WHEN("the list is pushed to itself")
					{
						list.Push(list);
						THEN("the size doubles")
						{
							REQUIRE(list.GetLength() == 12);
						}
						AND_THEN("the header is no longer the previous header")
						{
							REQUIRE(*list.GetHeader() != *currentHeader);
						}
						AND_THEN("the header points to the old header when increased by six")
						{
							REQUIRE(*(list.GetHeader() += 6) == *currentHeader);
						}
						AND_THEN("the list is correct")
						{
							REQUIRE(list[0] == 5);
							REQUIRE(list[1] == 5);
							REQUIRE(list[2] == 1);
							REQUIRE(list[3] == 5);
							REQUIRE(list[4] == 2);
							REQUIRE(list[5] == 1);
							REQUIRE(list[6] == 4);
							REQUIRE(list[7] == 5);
							REQUIRE(list[8] == 6);
							REQUIRE(list[9] == 2);
							REQUIRE(list[10] == 3);
							REQUIRE(list[11] == 1);
						}
					}
					AND_WHEN("one thing is pushed at a position greater than the length of the list")
					{
						THEN("throw an exception")
						{
							REQUIRE_THROWS([&]()
							{
								list.Push(100, 20);
							}());
						}
					}
					AND_WHEN("one thing is pushed at a position < 0")
					{
						THEN("throw an exception")
						{
							REQUIRE_THROWS([&]()
							{
								list.Push(100, -1);
							}());
						}
					}
					AND_WHEN("one thing is pushed at a valid position")
					{
						THEN("success")
						{
							list.Push(100, 3);
							REQUIRE(list[3] == 100);
						}
					}
				}
			}

		}
		AND_WHEN("one thing is appended")
		{
			list.Append(1);
			currentHeader = list.GetHeader();

			THEN("the size changes")
			{
				REQUIRE(list.GetLength() == 1);
			}
			AND_THEN("the header is no longer null")
			{
				REQUIRE(*currentHeader != nullptr);
			}
			AND_WHEN("two things are appended by array")
			{
				int arr[2] = { 2,3 };
				list.Append(2, arr);

				THEN("the size changes")
				{
					REQUIRE(list.GetLength() == 3);
				}
				AND_THEN("the header is the old header")
				{
					REQUIRE(*list.GetHeader() == *currentHeader);
				}
				AND_THEN("the header does not point to the old header when increased by two")
				{
					REQUIRE(*(list.GetHeader() += 2) != *currentHeader);
				}

				AND_WHEN("three things are appended by initializer list")
				{
					list.Append({ 4,5,6 });

					THEN("the size changes again")
					{
						REQUIRE(list.GetLength() == 6);
					}
					AND_THEN("the header is still the previous header")
					{
						REQUIRE(*list.GetHeader() == *currentHeader);
					}
					AND_THEN("the header does not point to the old header when increased by three")
					{
						REQUIRE(*(list.GetHeader() += 3) != *currentHeader);
					}

					AND_WHEN("a copy of the list is appended to itself")
					{
						auto listCpy = list;
						list.Append(listCpy);

						THEN("the size doubles")
						{
							REQUIRE(list.GetLength() == 12);
						}
						AND_THEN("the header is still the previous header")
						{
							REQUIRE(*list.GetHeader() == *currentHeader);
						}
						AND_THEN("the header does not point to the old header when increased by six")
						{
							REQUIRE(*(list.GetHeader() += 6) != *currentHeader);
						}
						AND_THEN("the list is correct")
						{
							REQUIRE(list[0] == 1);
							REQUIRE(list[1] == 2);
							REQUIRE(list[2] == 3);
							REQUIRE(list[3] == 4);
							REQUIRE(list[4] == 5);
							REQUIRE(list[5] == 6);
							REQUIRE(list[6] == 1);
							REQUIRE(list[7] == 2);
							REQUIRE(list[8] == 3);
							REQUIRE(list[9] == 4);
							REQUIRE(list[10] == 5);
							REQUIRE(list[11] == 6);
						}
					}
					AND_WHEN("the list is appended to itself")
					{
						list.Append(list);
						THEN("the size doubles")
						{
							REQUIRE(list.GetLength() == 12);
						}
						AND_THEN("the header is still the previous header")
						{
							REQUIRE(*list.GetHeader() == *currentHeader);
						}
						AND_THEN("the header does not point to the old header when increased by six")
						{
							REQUIRE(*(list.GetHeader() += 6) != *currentHeader);
						}
						AND_THEN("the list is correct")
						{
							REQUIRE(list[0] == 1);
							REQUIRE(list[1] == 2);
							REQUIRE(list[2] == 3);
							REQUIRE(list[3] == 4);
							REQUIRE(list[4] == 5);
							REQUIRE(list[5] == 6);
							REQUIRE(list[6] == 1);
							REQUIRE(list[7] == 2);
							REQUIRE(list[8] == 3);
							REQUIRE(list[9] == 4);
							REQUIRE(list[10] == 5);
							REQUIRE(list[11] == 6);
						}
					}
				}
			}
		}

	}
	GIVEN("A list that is initialized with an array of 2 integers")
	{
		int arr[2] = { 10,9 };
		KC::LinkedList<int> list(2, arr);
		WHEN("nothing is done to it")
		{
			THEN("the length is correct")
			{
				REQUIRE(list.GetLength() == 2);
			}
			AND_THEN("the header points to nothing")
			{
				REQUIRE(*list.GetHeader() != nullptr);
			}
		}

		AND_WHEN("pulled from using a function")
		{
			auto headNode = list.GetHeader();
			auto a = list.Pull();

			THEN("the data is correctly pulled")
			{
				REQUIRE(a == 10);
			}
			AND_THEN("the list is resized acccordingly")
			{
				REQUIRE(list.GetLength() == 1);
			}
		}

		AND_WHEN("pulled from using operators")
		{
			auto headNode = list.GetHeader();
			int a;
			list >> a;

			THEN("the data is correctly pulled")
			{
				REQUIRE(a == 10);
			}
			AND_THEN("the list is resized acccordingly")
			{
				REQUIRE(list.GetLength() == 1);
			}
		}
		AND_WHEN("pulled from multiple times using operators")
		{
			auto headNode = list.GetHeader();
			int a, b;
			list >> a >> b;

			THEN("the data is correctly pulled")
			{
				REQUIRE(a == 10);
				REQUIRE(b == 9);
			}
			AND_THEN("the list is resized acccordingly")
			{
				REQUIRE(list.GetLength() == 0);
			}
			AND_THEN("the list's header is now a nullptr")
			{
				REQUIRE(*list.GetHeader() == nullptr);
			}
		}
		AND_WHEN("accessing an index larger than the length of the list")
		{
			THEN("throws an exception")
			{
				REQUIRE_THROWS([&]()
				{
					auto a = list[2];
				}());
			}
		}
		AND_WHEN("accessing a negative index")
		{
			THEN("throws an exception")
			{
				REQUIRE_THROWS([&]()
				{
					auto a = list[-1];
				}());
			}
		}
	}
	GIVEN("A list is initialized with an initializer_list of 3 integers")
	{
		KC::LinkedList<int> list({ 100,10,1 });
		WHEN("nothing is done")
		{
			THEN("the list has the correct length")
			{
				REQUIRE(list.GetLength() == 3);
			}
			AND_THEN("the list's header exists")
			{
				REQUIRE(*list.GetHeader() != nullptr);
			}
			AND_THEN("the list is correct")
			{
				REQUIRE(list[0] == 100);
				REQUIRE(list[1] == 10);
				REQUIRE(list[2] == 1);
			}
		}
		AND_WHEN("an integer is added with an operator")
		{
			auto header = list.GetHeader();
			list << 5;
			THEN("the list has the correct length")
			{
				REQUIRE(list.GetLength() == 4);
			}
			AND_THEN("the list's header equals the previous header")
			{
				REQUIRE(*list.GetHeader() == *header);
			}
			AND_THEN("the list's header + 1 is not equal to the previous header")
			{
				REQUIRE(*(list.GetHeader() + 1) != *header);
			}
			AND_THEN("the value at the end of the list is the integer we added")
			{
				REQUIRE(list.End()->Data == 5);
			}
		}
	}
}
SCENARIO("KC::LinkedList<char> is an expanded version of KC::List<char>", "[LinkedList][char][LinkedList<char>][List][List<char>][Data Structure][Derived]")
{
	GIVEN("A list that is initialized with nothing ")
	{
		KC::LinkedList<char> list;
		WHEN("nothing is added to the list")
		{
			THEN("the list has nothing inside of it")
			{
				REQUIRE(list.GetLength() == 0);
			}
			AND_THEN("the list's header is pointing to nothing")
			{
				REQUIRE(*list.GetHeader() == nullptr);
			}
		}

		KC::TraversalNode<char> currentHeader;

		AND_WHEN("one thing is pushed")
		{
			list.Push('a');
			currentHeader = list.GetHeader();

			THEN("the size changes")
			{
				REQUIRE(list.GetLength() == 1);
			}
			AND_THEN("the header is no longer null")
			{
				REQUIRE(*currentHeader != nullptr);
			}
			AND_WHEN("two things are pushed by array")
			{
				char arr[2] = { 'b','c' };
				list.Push(2, arr);

				THEN("the size changes")
				{
					REQUIRE(list.GetLength() == 3);
				}
				AND_THEN("the header is not the old header")
				{
					REQUIRE(*list.GetHeader() != *currentHeader);
				}
				AND_THEN("the header points to the old header when increased by two")
				{
					REQUIRE(*(list.GetHeader() += 2) == *currentHeader);
				}

				currentHeader = list.GetHeader();

				AND_WHEN("three things are pushed by initializer list")
				{
					list.Push({ 'd','e','f' });

					THEN("the size changes again")
					{
						REQUIRE(list.GetLength() == 6);
					}
					AND_THEN("the header is no longer the previous header")
					{
						REQUIRE(*list.GetHeader() != *currentHeader);
					}
					AND_THEN("the header points to the old header when increased by three")
					{
						REQUIRE(*(list.GetHeader() += 3) == *currentHeader);
					}

					currentHeader = list.GetHeader();

					AND_WHEN("a copy of the list is pushed to itself")
					{
						auto listCpy = list;
						list.Push(listCpy);

						THEN("the size doubles")
						{
							REQUIRE(list.GetLength() == 12);
						}
						AND_THEN("the header is no longer the previous header")
						{
							REQUIRE(*list.GetHeader() != *currentHeader);
						}
						AND_THEN("the header points to the old header when increased by six")
						{
							REQUIRE(*(list.GetHeader() += 6) == *currentHeader);
						}
						AND_THEN("the list is correct")
						{
							REQUIRE(list[0] == 'd');
							REQUIRE(list[1] == 'e');
							REQUIRE(list[2] == 'f');
							REQUIRE(list[3] == 'b');
							REQUIRE(list[4] == 'c');
							REQUIRE(list[5] == 'a');
							REQUIRE(list[6] == 'd');
							REQUIRE(list[7] == 'e');
							REQUIRE(list[8] == 'f');
							REQUIRE(list[9] == 'b');
							REQUIRE(list[10] == 'c');
							REQUIRE(list[11] == 'a');
						}
					}
					AND_WHEN("the list is pushed to itself")
					{
						list.Push(list);
						THEN("the size doubles")
						{
							REQUIRE(list.GetLength() == 12);
						}
						AND_THEN("the header is no longer the previous header")
						{
							REQUIRE(*list.GetHeader() != *currentHeader);
						}
						AND_THEN("the header points to the old header when increased by six")
						{
							REQUIRE(*(list.GetHeader() += 6) == *currentHeader);
						}
						AND_THEN("the list is correct")
						{
							REQUIRE(list[0] == 'e');
							REQUIRE(list[1] == 'e');
							REQUIRE(list[2] == 'a');
							REQUIRE(list[3] == 'e');
							REQUIRE(list[4] == 'b');
							REQUIRE(list[5] == 'a');
							REQUIRE(list[6] == 'd');
							REQUIRE(list[7] == 'e');
							REQUIRE(list[8] == 'f');
							REQUIRE(list[9] == 'b');
							REQUIRE(list[10] == 'c');
							REQUIRE(list[11] == 'a');
						}
					}
					AND_WHEN("one thing is pushed at a position greater than the length of the list")
					{
						THEN("throw an exception")
						{
							REQUIRE_THROWS([&]()
							{
								list.Push('a', 20);
							}());
						}
					}
					AND_WHEN("one thing is pushed at a position < 0")
					{
						THEN("throw an exception")
						{
							REQUIRE_THROWS([&]()
							{
								list.Push('a', -1);
							}());
						}
					}
					AND_WHEN("one thing is pushed at a valid position")
					{
						THEN("success")
						{
							list.Push('a', 3);
							REQUIRE(list[3] == 'a');
						}
					}
				}
			}

		}
		AND_WHEN("one thing is appended")
		{
			list.Append('a');
			currentHeader = list.GetHeader();

			THEN("the size changes")
			{
				REQUIRE(list.GetLength() == 1);
			}
			AND_THEN("the header is no longer null")
			{
				REQUIRE(*currentHeader != nullptr);
			}
			AND_WHEN("two things are appended by array")
			{
				char arr[2] = { 'b','c' };
				list.Append(2, arr);

				THEN("the size changes")
				{
					REQUIRE(list.GetLength() == 3);
				}
				AND_THEN("the header is the old header")
				{
					REQUIRE(*list.GetHeader() == *currentHeader);
				}
				AND_THEN("the header does not point to the old header when increased by two")
				{
					REQUIRE(*(list.GetHeader() += 2) != *currentHeader);
				}

				AND_WHEN("three things are appended by initializer list")
				{
					list.Append({ 'd','e','f' });

					THEN("the size changes again")
					{
						REQUIRE(list.GetLength() == 6);
					}
					AND_THEN("the header is still the previous header")
					{
						REQUIRE(*list.GetHeader() == *currentHeader);
					}
					AND_THEN("the header does not point to the old header when increased by three")
					{
						REQUIRE(*(list.GetHeader() += 3) != *currentHeader);
					}

					AND_WHEN("a copy of the list is appended to itself")
					{
						auto listCpy = list;
						list.Append(listCpy);

						THEN("the size doubles")
						{
							REQUIRE(list.GetLength() == 12);
						}
						AND_THEN("the header is still the previous header")
						{
							REQUIRE(*list.GetHeader() == *currentHeader);
						}
						AND_THEN("the header does not point to the old header when increased by six")
						{
							REQUIRE(*(list.GetHeader() += 6) != *currentHeader);
						}
						AND_THEN("the list is correct")
						{
							REQUIRE(list[0] == 'a');
							REQUIRE(list[1] == 'b');
							REQUIRE(list[2] == 'c');
							REQUIRE(list[3] == 'd');
							REQUIRE(list[4] == 'e');
							REQUIRE(list[5] == 'f');
							REQUIRE(list[6] == 'a');
							REQUIRE(list[7] == 'b');
							REQUIRE(list[8] == 'c');
							REQUIRE(list[9] == 'd');
							REQUIRE(list[10] == 'e');
							REQUIRE(list[11] == 'f');
						}
					}
					AND_WHEN("the list is appended to itself")
					{
						list.Append(list);
						THEN("the size doubles")
						{
							REQUIRE(list.GetLength() == 12);
						}
						AND_THEN("the header is still the previous header")
						{
							REQUIRE(*list.GetHeader() == *currentHeader);
						}
						AND_THEN("the header does not point to the old header when increased by six")
						{
							REQUIRE(*(list.GetHeader() += 6) != *currentHeader);
						}
						AND_THEN("the list is correct")
						{
							REQUIRE(list[0] == 'a');
							REQUIRE(list[1] == 'b');
							REQUIRE(list[2] == 'c');
							REQUIRE(list[3] == 'd');
							REQUIRE(list[4] == 'e');
							REQUIRE(list[5] == 'f');
							REQUIRE(list[6] == 'a');
							REQUIRE(list[7] == 'b');
							REQUIRE(list[8] == 'c');
							REQUIRE(list[9] == 'd');
							REQUIRE(list[10] == 'e');
							REQUIRE(list[11] == 'f');
						}
					}
				}
			}
		}

	}
	GIVEN("A list that is initialized with an array of 2 integers")
	{
		char arr[2] = { 'a','b' };
		KC::LinkedList<char> list(2, arr);
		WHEN("nothing is done to it")
		{
			THEN("the length is correct")
			{
				REQUIRE(list.GetLength() == 2);
			}
			AND_THEN("the header points to nothing")
			{
				REQUIRE(*list.GetHeader() != nullptr);
			}
		}

		AND_WHEN("pulled from using a function")
		{
			auto headNode = list.GetHeader();
			auto a = list.Pull();

			THEN("the data is correctly pulled")
			{
				REQUIRE(a == 'a');
			}
			AND_THEN("the list is resized acccordingly")
			{
				REQUIRE(list.GetLength() == 1);
			}
		}

		AND_WHEN("pulled from using operators")
		{
			auto headNode = list.GetHeader();
			char a;
			list >> a;

			THEN("the data is correctly pulled")
			{
				REQUIRE(a == 'a');
			}
			AND_THEN("the list is resized acccordingly")
			{
				REQUIRE(list.GetLength() == 1);
			}
		}
		AND_WHEN("pulled from multiple times using operators")
		{
			auto headNode = list.GetHeader();
			char a, b;
			list >> a >> b;

			THEN("the data is correctly pulled")
			{
				REQUIRE(a == 'a');
				REQUIRE(b == 'b');
			}
			AND_THEN("the list is resized acccordingly")
			{
				REQUIRE(list.GetLength() == 0);
			}
			AND_THEN("the list's header is now a nullptr")
			{
				REQUIRE(*list.GetHeader() == nullptr);
			}
		}
		AND_WHEN("accessing an index larger than the length of the list")
		{
			THEN("throws an exception")
			{
				REQUIRE_THROWS([&]()
				{
					auto a = list[2];
				}());
			}
		}
		AND_WHEN("accessing a negative index")
		{
			THEN("throws an exception")
			{
				REQUIRE_THROWS([&]()
				{
					auto a = list[-1];
				}());
			}
		}
	}
	GIVEN("A list is initialized with an initializer_list of 3 integers")
	{
		KC::LinkedList<char> list({ 'x','y','z' });
		WHEN("nothing is done")
		{
			THEN("the list has the correct length")
			{
				REQUIRE(list.GetLength() == 3);
			}
			AND_THEN("the list's header exists")
			{
				REQUIRE(*list.GetHeader() != nullptr);
			}
			AND_THEN("the list is correct")
			{
				REQUIRE(list[0] == 'x');
				REQUIRE(list[1] == 'y');
				REQUIRE(list[2] == 'z');
			}
		}
		AND_WHEN("an integer is added with an operator")
		{
			auto header = list.GetHeader();
			list << 'a';
			THEN("the list has the correct length")
			{
				REQUIRE(list.GetLength() == 4);
			}
			AND_THEN("the list's header equals the previous header")
			{
				REQUIRE(*list.GetHeader() == *header);
			}
			AND_THEN("the list's header + 1 is not equal to the previous header")
			{
				REQUIRE(*(list.GetHeader() + 1) != *header);
			}
			AND_THEN("the value at the end of the list is the integer we added")
			{
				REQUIRE(list.End()->Data == 'a');
			}
		}
	}
}