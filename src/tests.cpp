#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Тест на создание ленты, чтения файла
TEST(tape_interface_test, file_reading)
{

}

// Тест на загрузку в ленту несуществующего файла

// Тест на загрузку в ленту файла с невалидными данными

// Тест алгоритма сортировки: разбиение на несколько лент, сортировка

int main(int argc, char** argv)
{
    // ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}