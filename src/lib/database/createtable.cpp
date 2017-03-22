#include "createtable.h"

#include "logger.h"

CreateTable::CreateTable(std::string tableName) : m_tableName(tableName)
{

}

CreateTable::~CreateTable()
{

}

bool CreateTable::appendColumn(std::string columnName, SQLTypes::ColumnType columnType)
{

}
