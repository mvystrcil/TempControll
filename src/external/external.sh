#!/bin/bash

function makeSQLiteLib()
{
	GCC=$1
	BASE=$2
	SRC=$3
	BUILD_PATH=$4

	CURR=`pwd`
	LIB="$BASE/$BUILD_PATH/"

	# Check if already compiled ...
	if [ -f "$LIB/libsqlite.so" ]
	then
		echo "Already compiled"
		return 0
	fi

	echo "Make SQLite $@"
	cd "$BASE/$SRC/sqlite"
	$GCC -c -fPIC sqlite3.c -o "$LIB/sqlite.o"
	$GCC -shared -Wl,-sonam,"$LIB/libsqlite.so" -o "$LIB/libsqlite.so" "$LIB/sqlite.o"
	#cp libsqlite.so "$BASE/$BUILD_PATH"
}

makeSQLiteLib $@

cd $2
