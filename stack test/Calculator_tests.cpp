#include "pch.h"
#include "..\mp2-lab3-stack\stack.h"
#include "..\mp2-lab3-stack\Token.h"
#include "..\mp2-lab3-stack\Calculator.h"

TEST(Calculator, can_convert_str_to_infix_conteiner) {
	std::string ezz_str = "(2+3)", med_str = "((2.3+5.51)*10.89342+54/8)",
		diff_str = "(((3.8428746825775*678.5437877)/(577.545674325678))*34.185-235.29+127)";
	Calculator ezz("2 + 3"), med("(2.3 + 5.51) * 10.89342 + 54 / 8"),
		diff("((3.8428746825775 * 678.5437877)/(577.545674325678))*34.185 - 235.29 + 127");
	ASSERT_NO_THROW(ezz.infix_to_cont());
	ASSERT_NO_THROW(med.infix_to_cont());
	ASSERT_NO_THROW(diff.infix_to_cont());

	ASSERT_EQ(ezz.get_inf_cont().cont_to_string(), ezz_str);
	ASSERT_EQ(med.get_inf_cont().cont_to_string(), med_str);
	ASSERT_EQ(diff.get_inf_cont().cont_to_string(), diff_str);

}

TEST(Calculator, infix_container_not_equeal_with_rand_str) {
	std::string rand_str = "", ezz_str = "(2+3)", med_str = "((2.3+5.51)*10.89342+54/8)";
	Calculator ezz("2 + 3"), med("(2.3 + 5.51) * 10.89342 + 54 / 8"),
		diff("((3.8428746825775 * 678.5437877)/(577.545674325678))*34.185 - 235.29 + 127");
	ezz.infix_to_cont();
	med.infix_to_cont();
	diff.infix_to_cont();
	ASSERT_NE(ezz.get_inf_cont().cont_to_string(), rand_str);
	ASSERT_NE(med.get_inf_cont().cont_to_string(), rand_str);

}

TEST(Calculator, can_convert_to_postfix_conteiner) {
	std::string rand_str = "", ezz_str = "(2+3)", medium_str = "((2.3+5.51)*10.89342+54/8)",
		post_ezz = "23+", post_medium = "2.35.51+10.89342*548/+";
	Calculator ezz("2 + 3"), med("(2.3 + 5.51) * 10.89342 + 54 / 8");
	ezz.infix_to_cont();
	med.infix_to_cont();
	ASSERT_NO_THROW(ezz.infix_cont_to_postfix_cont());
	ASSERT_NO_THROW(med.infix_cont_to_postfix_cont());
	ASSERT_EQ(ezz.get_post_cont().cont_to_string(), post_ezz);
	ASSERT_EQ(med.get_post_cont().cont_to_string(), post_medium);
}

TEST(Calculator, postfix_container_not_equeal_with_rand_str) {
	std::string rand_str = "", ezz_str = "(2+3)", medium_str = "((2.3+5.51)*10.89342+54/8)";
	Calculator ezz("2 + 3"), med("(2.3 + 5.51) * 10.89342 + 54 / 8");
	ezz.infix_to_cont();
	med.infix_to_cont();
	ezz.infix_cont_to_postfix_cont();
	med.infix_cont_to_postfix_cont();
	ASSERT_NE(ezz.get_post_cont().cont_to_string(), rand_str);
	ASSERT_NE(med.get_post_cont().cont_to_string(), rand_str);
}


TEST(Calculator, can_caclculate_with_correct_result){
	std::string ezz_str = "(2+3)", medium_str = "((2.3+5.51)*10.89342+54/8)",
		diff_str = "(((3.8428746825775*678.5437877)/(577.545674325678))*34.185-235.29+127)";
	Calculator ezz("2 + 3"), med("(2.3 + 5.51) * 10.89342 + 54 / 8"),diff("((3.8428746825775*678.5437877)/(577.545674325678))*34.185-235.29+127");
	ezz.infix_to_cont();
	med.infix_to_cont();
	diff.infix_to_cont();
	ezz.infix_cont_to_postfix_cont();
	med.infix_cont_to_postfix_cont();
	diff.infix_cont_to_postfix_cont();
	ASSERT_NO_THROW(ezz.Calculate_postfix());
	ASSERT_NO_THROW(med.Calculate_postfix());
	ASSERT_NO_THROW(diff.Calculate_postfix());
	ASSERT_DOUBLE_EQ(ezz.Calculate_postfix(), 2 + 3);
	ASSERT_DOUBLE_EQ(med.Calculate_postfix(), (2.3 + 5.51) * 10.89342 + 54.0 / 8.0);
	ASSERT_DOUBLE_EQ(diff.Calculate_postfix(), ((3.8428746825775 * 678.5437877) / (577.545674325678)) * 34.185 - 235.29 + 127);
	ASSERT_NE(ezz.Calculate_postfix(),42);

}

TEST(Calculator, thorow_if_incorrect_count_open_brackets_at_beginning) {
	Calculator inc("(((((2+3)*(3-4))");
	inc.infix_to_cont();
	ASSERT_ANY_THROW(inc.infix_cont_to_postfix_cont());
}

TEST(Calculator, thorow_if_incorrect_cnt_open_brackets) {
	Calculator inc("((2+3)*((3-4))");
	inc.infix_to_cont();
	ASSERT_ANY_THROW(inc.infix_cont_to_postfix_cont());
}

TEST(Calculator, thorow_if_incorrect_count_close_brackets_at_end) {
	Calculator inc("((2+3)*(3-4))))))");
	inc.infix_to_cont();
	ASSERT_ANY_THROW(inc.infix_cont_to_postfix_cont());
}

TEST(Calculator, thorow_if_incorrect_count_operations_at_beginning) {
	Calculator inc("--+*/((2+3)*(3-4))");
	ASSERT_ANY_THROW(inc.Calculate());
}

TEST(Calculator, thorow_if_incorrect_count_operations_at_end) {
	Calculator inc("((2+3)*(3-4))--+*/");
	ASSERT_ANY_THROW(inc.Calculate());
}

TEST(Calculator, thorow_if_incorrect_count_operations) {
	Calculator inc1("((2+3)*(3-4)-)"), inc2("2.1457+++785.0"), inc3("546.0124/*6789");
	ASSERT_ANY_THROW(inc1.Calculate());
	ASSERT_ANY_THROW(inc2.Calculate());
	ASSERT_ANY_THROW(inc3.Calculate());
}
TEST(Calculator, thorow_if_incorrect_count_numbers) {
	Calculator inc1("2 + 3 4 5 66 78 9"), inc2("2 + 3 * 4 / (5 + 66 78) * 9");
	ASSERT_ANY_THROW(inc1.Calculate());
	ASSERT_ANY_THROW(inc2.Calculate());
	
}
TEST(Calculator, thorow_if_void_str) {
	Calculator inc1(""), inc2("     ");
	ASSERT_ANY_THROW(inc1.Calculate());
	ASSERT_ANY_THROW(inc2.Calculate());

}

TEST(Calculator, correct_read_float_numbers) {
	Calculator flt("0.512 - 0.012");
	double res = 0.0;
	ASSERT_NO_THROW(res = flt.Calculate());
	ASSERT_NEAR(res, 0.5, 1e-9);
}

TEST(Calculator, thorow_if_incorrect_count_close_brackets) {
	Calculator inc("((2+3))*(3-4))");
	inc.infix_to_cont();
	ASSERT_ANY_THROW(inc.infix_cont_to_postfix_cont());
}

TEST(Calculator, correct_order_of_same_operations) {
	Calculator div("2/3/4/5");
	ASSERT_EQ(div.Calculate(), 2.0 / 3.0 / 4.0 / 5);
}

TEST(Calculator, correct_order_of_different_types_operations) {
	Calculator first("(2+2)*2"),second("2+2*2");
	ASSERT_EQ(first.Calculate(), 8);
	ASSERT_EQ(second.Calculate(), 6);
}
TEST(Calculator, double_calcuate_call_doesnt_change_result) {
	Calculator el("2+2*2"),calc_post("6 + 2");
	calc_post.infix_to_cont();
	calc_post.infix_cont_to_postfix_cont();
	calc_post.Calculate_postfix();
	calc_post.Calculate_postfix();
	ASSERT_EQ(calc_post.Calculate_postfix(),8);
	el.Calculate();
	el.Calculate();
	ASSERT_EQ(el.Calculate(), 6);

}