#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ustr.h"
#include "pset1.h"

/*
Initializes a new UStr with contents
*/
UStr new_ustr(char* contents) {
	int32_t bytes = strlen(contents);
	int32_t codepoints = utf8_strlen(contents);
	uint8_t all_ascii = bytes == codepoints;
	char* contents_copy = malloc(bytes + 1);
	strcpy(contents_copy, contents);
	UStr s = {
		codepoints,
		bytes,
		all_ascii,
		contents_copy
	};
	return s;
}

/*
Returns length of string
*/
int32_t len(UStr s) {
	return s.codepoints;
}

/*
Returns a substring of str, starting at index start (inclusive) 
and ending at index end (exclusive).

Returns an empty string on invalid range.
*/
UStr substring(UStr s, int32_t start, int32_t end) {
	// TODO: implement this
	if(start < 0 || end > len(s) || end <= start) {
		return new_ustr("");
	} else {
		int32_t bi_start = bi_of_cpi(s.contents, start);
		int32_t bi_end = bi_of_cpi(s.contents, end);
		char * temp = calloc((bi_end - bi_start + 1), sizeof(char));
		temp = strncpy(temp, s.contents + bi_start, bi_end - bi_start);
		if (temp == NULL) {
			perror("strncpy error");
		}
		UStr subs = new_ustr(temp);
		free(temp);
		return subs;
	}
}

/*
Given 2 strings s1 and s2, returns a string that is the result of 
concatenating s1 and s2. 
*/
UStr concat(UStr s1, UStr s2) {
	char buffer[1024];
	strncpy(buffer, s1.contents, len(s1));
	strncpy(buffer + len(s1), s2.contents, len(s2));
	buffer[strlen(buffer)] = 0;
	free(s1.contents);
	free(s2.contents);
	return new_ustr(buffer);
}

/*
Given a string s and an index, return a string with the character at index 
removed from the original string. 

Returns the original string if index is out of bounds.
*/
UStr removeAt(UStr s, int32_t index) {
	// TODO: implement this

}

/*
Given a string s, return s reversed. 

Example: reverse("apples🍎 and bananas🍌") = "🍌sananab dna 🍎selppa")
*/
UStr reverse(UStr s) {
	// TODO: implement this

}


void print_ustr(UStr s) {
	printf("%s [codepoints: %d | bytes: %d]", s.contents, s.codepoints, s.bytes);
}

void free_ustr(UStr s) {
	if (s.contents != NULL) {
		free(s.contents);
		s.contents = NULL;
	}
}

