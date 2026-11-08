#include "pch.h"

#include "..\mp2-lab3-stack\stack.h"

TEST(TDynamicStack, can_create_stack_with_pos_leight) {
	ASSERT_NO_THROW(TDynamicStack<int> st(7));
}

TEST(TDynamicStack, can_not_create_stack_with_negative_leight) {
	ASSERT_ANY_THROW(TDynamicStack<int> st(-7));
}

TEST(TDynamicStack, can_fill_stack) {
	TDynamicStack<int> st(7);
	for (int i = 0; i < 7; i++) {
		ASSERT_NO_THROW(st.push(i));
	}
}

TEST(TDynamicStack, empty_stack_check_empty_true){
	TDynamicStack<int> st(7);
	ASSERT_TRUE(st.IsEmpty());
}
TEST(TDynamicStack, empty_stack_check_full_false) {
	TDynamicStack<int> st(7);
	ASSERT_FALSE(st.IsFull());
}

TEST(TDynamicStack, full_stack_check_empty_false) {
	TDynamicStack<int> st(7);
	for (int i = 0; i < 7; i++) {
		st.push(i);
	}
	ASSERT_FALSE(st.IsEmpty());
}
TEST(TDynamicStack, full_stack_check_full_true) {
	TDynamicStack<int> st(7);
	for (int i = 0; i < 7; i++) {
		st.push(i);
	}
	ASSERT_TRUE(st.IsFull());
}

TEST(TDynamicStack, can_get_from_stack) {
	TDynamicStack<int> st(7);
	for (int i = 0; i < 7; i++) {
		st.push(i);
	}
	for (int i = 6; i > -1; i--) {
		ASSERT_EQ(st.pop(), i);
	}
}

TEST(TDynamicStack, can_appropriate_stack_with_same_leight) {
	TDynamicStack<int> st(7);{}
	for (int i = 0; i < 7; i++) {
		(st.push(i));
	}
	TDynamicStack<int> st_cp(7); 
	ASSERT_NO_THROW(st_cp = st);
	ASSERT_EQ(st_cp, st);

}


TEST(TDynamicStack, can_appropriate_stack_with_different_leight) {
	TDynamicStack<int> st(7); {}
	for (int i = 0; i < 7; i++) {
		(st.push(i));
	}
	TDynamicStack<int> st_cp(1);
	ASSERT_NO_THROW(st_cp = st);
	ASSERT_EQ(st_cp, st);

}

TEST(TDynamicStack, can_copy_stack)
{
	TDynamicStack<int> st(7);
	for (int i = 0; i < 7; i++) {
		(st.push(i));
	}
	TDynamicStack<int> stcp(st);
	ASSERT_EQ(stcp, st);
}

TEST(TDynamicStack, stack_copy_have_own_memory)
{
	TDynamicStack<int> st(7);
	for (int i = 0; i < 7; i++) {
		(st.push(i));
	}
	TDynamicStack<int> stcp(st);
	ASSERT_NE(&stcp, &st);
}

TEST(TDynamicStack, compare_stack_with_itself_return_true) {
	TDynamicStack<int> st(7); 
	for (int i = 0; i < 7; i++) {
		(st.push(i));
	}
	ASSERT_NO_THROW(st== st);
	ASSERT_EQ(st, st);

}

TEST(TDynamicStack, compare_stacks_with_equeal_size_return_true) {
	TDynamicStack<int> st(7); {}
	for (int i = 0; i < 7; i++) {
		(st.push(i));
	}
	TDynamicStack<int> st_(7); {}
	for (int i = 0; i < 7; i++) {
		(st_.push(i));
	}
	ASSERT_NO_THROW(st_ == st);
	ASSERT_EQ(st_, st);
}

TEST(TDynamicStack, compare_stacks_with_not_equeal_size_return_false) {
	TDynamicStack<int> st(7); {}
	for (int i = 0; i < 7; i++) {
		(st.push(i));
	}
	TDynamicStack<int> st_(6); {}
	for (int i = 0; i < 6; i++) {
		(st_.push(i));
	}
	
	ASSERT_NE(st_, st);
}

/*TEST(TDynamicStack, cant_push_in_full_stack) {
	TDynamicStack<int> st(7); {}
	for (int i = 0; i < 7; i++) {
		(st.push(i));
	}
	ASSERT_ANY_THROW(st.push(9));
}*/

TEST(TDynamicStack, cant_pop_in_empty_stack) {
	TDynamicStack<int> st(7); {}
	
	ASSERT_ANY_THROW(st.pop());
}

