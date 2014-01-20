#include "common.h"
#define CATCH_CONFIG_MAIN
#include "Catch/single_include/catch.hpp"

#include <sstream>

using namespace kontr;
using namespace std;

TEST_CASE("Perl code"){
    Testing& cg = Testing::instance();
    using T = Testing;
    stringstream ss;
    cg.storage.out_ptr = &ss;

    PERL("$b = $cd + 3a;");
    CHECK(ss.str() == "$b = $cd + 3a;\n");
}

TEST_CASE("if/else"){
    Testing& cg = Testing::instance();
    using T = Testing;
    stringstream ss;
    cg.storage.out_ptr = &ss;
    Variable::Delegator<Testing> a("a", 10);
    Variable::Delegator<Testing> b("b", 10);

    ss.str("");
    IF( b == 10, { a = 20; } );
    CHECK(ss.str() == "if ($b == 10) {\n$a = 20;\n}\n");

    ss.str("");
    IF( b == 10, a = 20; );
    CHECK(ss.str() == "if ($b == 10) {\n$a = 20;\n}\n");

    ss.str("");
    IF( b == 10, { a = 20; }, { a = 30; } );
    CHECK(ss.str() == "if ($b == 10) {\n$a = 20;\n} else {\n$a = 30;\n}\n");

    ss.str("");
    IF( b == 10, { a = 20; }, a = 30; );
    CHECK(ss.str() == "if ($b == 10) {\n$a = 20;\n} else {\n$a = 30;\n}\n");

    ss.str("");
    IF( b == 10, a = 20; , a = 30; );
    CHECK(ss.str() == "if ($b == 10) {\n$a = 20;\n} else {\n$a = 30;\n}\n");
}

TEST_CASE("while"){
    Testing& cg = Testing::instance();
    using T = Testing;
    stringstream ss;
    cg.storage.out_ptr = &ss;
    Variable::Delegator<Testing> a("a", 10);
    Variable::Delegator<Testing> b("b", 10);

    ss.str("");
    WHILE( b == 10, { a = 20; } );
    CHECK(ss.str() == "while ($b == 10) {\n$a = 20;\n}\n");

    ss.str("");
    WHILE( b == 10, a = 20; );
    CHECK(ss.str() == "while ($b == 10) {\n$a = 20;\n}\n");
}

TEST_CASE("Control flow"){
    Testing& cg = Testing::instance();
    using T = Testing;
    stringstream ss;
    cg.storage.out_ptr = &ss;

    ss.str("");
    RETURN();
    CHECK(ss.str() == "return;\n");

    ss.str("");
    BREAK();
    CHECK(ss.str() == "break;\n");

    ss.str("");
    CONTINUE();
    CHECK(ss.str() == "continue;\n");
}

TEST_CASE("Files"){
    Testing& cg = Testing::instance();
    using T = Testing;
    stringstream ss;
    cg.storage.out_ptr = &ss;

    Variable::Delegator<Testing> a("a", 10);

    ss.str("");
    a = FILE_EXISTS("tmp");
    CHECK(ss.str() == "$a = -e 'tmp';\n");

    a = "tmp";
    ss.str("");
    a = FILE_EXISTS(a + ".tmp");
    CHECK(ss.str() == "$a = -e ($a . '.tmp');\n");

    ss.str("");
    a = FILE_EMPTY("tmp");
    CHECK(ss.str() == "$a = -z 'tmp';\n");

    ss.str("");
    a = FILE_SIZE("tmp");
    CHECK(ss.str() == "$a = -s 'tmp';\n");

}
