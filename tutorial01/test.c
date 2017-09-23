#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leptjson.h"

static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

#define EXPECT_EQ_BASE(equality, expect, actual, format) \
    do {\
        test_count++;\
        if (equality)\
            test_pass++;\
        else {\
            fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", __FILE__, __LINE__, expect, actual);\
            main_ret = 1;\
        }\
    } while(0)

#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d")
#define EXPECT_EQ_DOUBLE(expect,actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual,"%lf")

#define TEST_ERROR(error,json) \
	do {\
		lept_value v;\
		v.type = LEPT_FALSE; \
		EXPECT_EQ_INT(LEPT_PARSE_OK,lept_parse(&v,json));\
		EXPECT_EQ_INT(error,lept_get_type(&v));\
	}while(0)

#define TEST_NUMBER(except, json) \
	do {\
		lept_value v;\
		v.type = LEPT_FALSE;\
		EXPECT_EQ_INT(LEPT_PARSE_OK,lept_parse(&v,json));\
		EXPECT_ER_INT(LEPT_NUMBER,let_get_type(&v) );\
		EXPECT_EQ_DOUBLE(except,lept_get_number(&v));\
	}while(0)

static void test_parse_null() {
	TEST_ERROR(LEPT_NULL, "null");
}

static void test_parse_true() {
	TEST_ERROR(LEPT_TRUE, "true");

static void test_parse_false() {
	TEST_ERROR(LEPT_FALSE, "false");
}

static void test_parse_expect_value() {
	TEST_ERROR(LEPT_NULL, " ");
	TEST_ERROR(LEPT_NULL, "");
}

static void test_parse_invalid_value() {
	TEST_ERROR(LEPT_NULL, "?");
	TEST_ERROR(LEPT_NULL, "nul");

	TEST_ERROR()
}

static void test_parse_root_not_singular() {
	TEST_ERROR(LEPT_NULL, "null x");
}

static void test_parse_number() {
	TEST_NUMBER(0.0, "0");
	TEST_NUMBER(0.0, "-0");
	TEST_NUMBER(0.0, "-0.0");
	TEST_NUMBER(1.0, "1");
	TEST_NUMBER(-1.0, "-1");
	TEST_NUMBER(1.5, "1.5");
	TEST_NUMBER(-1.5, "-1.5");
	TEST_NUMBER(3.1415926, "3.1415926");
	TEST_NUMBER(1E10, "1E10");
	TEST_NUMBER(1e10, "1e10");
	TEST_NUMBER(1E+10, "1E+10");
	TEST_NUMBER(1E-10, "1E-10");
	TEST_NUMBER(-1E10, "-1E10");
	TEST_NUMBER(-1e10, "-1e10");
	TEST_NUMBER(-1E+10, "-1E+10");
	TEST_NUMBER(-1E-10, "-1E-10");
	TEST_NUMBER(1.234E+10, "1.234E+10");
	TEST_NUMBER(1.234E-10, "1.234E-10");
	TEST_NUMBER(0.0, "1e-100000");
}


static void test_parse() {
    test_parse_null();
    test_parse_expect_value();
    test_parse_invalid_value();
    test_parse_root_not_singular();
	test_parse_true();
	test_parse_false();
}

int main() {
    test_parse();
    printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
    return main_ret;
}
