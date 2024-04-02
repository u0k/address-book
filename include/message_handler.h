#pragma once

enum message_codes {
	INVALID_INDEX	    = -1,
	EMPTY_LIST	    = -2,
	RECORD_CREATE_ERROR = -3,
	RECORD_DELETE_ERROR = -4,
	RECORD_NOT_FOUND    = -5,
	INVALID_SEARCH_KEY  = -6,
	INVALID_OPTION	    = -7,
	ERROR_LIST_CREATION = -8,
	ERROR_FILE_CLOSE    = -9,
	ERROR_LIST_DELETE   = -10,
	ERROR_SIGNAL_SET    = -11

};
void print_error_message(int message_code);