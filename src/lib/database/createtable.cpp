#include "createtable.h"

#include "logger.h"

CreateTable::CreateTable(std::string tableName, bool checkForExistence) : m_tableName(tableName), 
  m_checkForExistence(checkForExistence)
{

}

CreateTable::~CreateTable()
{

}

void CreateTable::checkIfExists(const bool checkForExistence)
{
  this->m_checkForExistence = checkForExistence;
}

bool CreateTable::appendColumn(std::string columnName, SQLTypes::ColumnType columnType)
{

}

std::string CreateTable::queryToString() const
{
  return "AA";
}