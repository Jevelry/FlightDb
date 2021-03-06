// Assignment 1 21T1 COMP2521: Flight Database
//
// This program was written by Kevin Huang (z5311917)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"
#include "FlightDb.h"
#include "AVLTree.h"

struct flightDb {
	Tree byFlightNumber;
	Tree byAirportDay;
	Tree byTime;
};

////////////////////////////////////////////////////////////////////////
// Basic Comparison functions

int byFlightNumber(Record r1, Record r2) {
    // Compare flight numbers
    return strcmp(RecordGetFlightNumber(r1), RecordGetFlightNumber(r2));          
}

int byAirport(Record r1, Record r2) {
    // Compare departure airport
    return strcmp(RecordGetDepartureAirport(r1), RecordGetDepartureAirport(r2));
}

int byDay(Record r1, Record r2) {
    // Compare day
    return RecordGetDepartureDay(r1) - RecordGetDepartureDay(r2);
}

int byHour(Record r1, Record r2) {
    // Compare hour
    return RecordGetDepartureHour(r1) - RecordGetDepartureHour(r2);
}

int byMin(Record r1, Record r2) {
    // Compare minute
    return RecordGetDepartureMinute(r1) - RecordGetDepartureMinute(r2);
}
////////////////////////////////////////////////////////////////////////
// Used Comparison functions

// Compares in order of day,hour,minute,flightnumber
int comparebyTime(Record r1, Record r2) {
    if (byDay(r1, r2) != 0) {
        return byDay(r1, r2);
    } else if (byHour(r1, r2) != 0) {
        return byHour(r1, r2);
    } else if (byMin(r1, r2) != 0) {
        return byMin(r1, r2);
    } else {
        return byFlightNumber(r1, r2);
    }
}
// Compares by flight number then by time
int comparebyFlightNumber(Record r1, Record r2) {
    if (byFlightNumber(r1,r2) != 0) {
        return byFlightNumber(r1,r2);
    } else {
        return comparebyTime(r1, r2);
    }
}
// Compares by departure airport then time then flight number
int comparebyDepartureAirportDay(Record r1, Record r2) {
    if (byAirport(r1, r2) != 0) {
        return byAirport(r1, r2); 
    } else {
        return comparebyTime(r1, r2);
    } 
}
// Creates a new flight DB. 
FlightDb DbNew(void) {
    // (from lab4 studentdb.c)
	FlightDb db = malloc(sizeof(*db));
	if (db == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }    
    db->byFlightNumber = TreeNew(comparebyFlightNumber);
	db->byAirportDay = TreeNew(comparebyDepartureAirportDay);
	db->byTime = TreeNew(comparebyTime);
    return db;
}

// Frees all memory allocated to the given flight DB
void     DbFree(FlightDb db) {
    // Based of studentdb.c Dbfree
	TreeFree(db->byFlightNumber, true);
	TreeFree(db->byAirportDay, false);
	TreeFree(db->byTime, false);	
	free(db);
}

/**
 * Inserts  a  flight  record  into the given DB if there is not already
 * record with the same flight number, departure airport, day, hour  and
 * minute.
 * If  inserted successfully, this function takes ownership of the given 
 * record (so the caller should not modify or free it). 
 * Returns true if the record was successfully inserted,  and  false  if
 * the  DB  already  contained  a  record  with  the same flight number,
 * departure airport, day, hour and minute.
 * The time complexity of this function must be O(log n).
 * You MUST use the AVLTree ADT (from Task 1) in your implementation.
 */
bool     DbInsertRecord(FlightDb db, Record r) {
    // Based of studentdb.c Dbinsertrecord
	if (TreeInsert(db->byFlightNumber, r)) {
        TreeInsert(db->byAirportDay, r);
        TreeInsert(db->byTime, r);                
        return true;
    } else {
        return false;
    }
}
	
/**
 * Searches  for  all  records with the given flight number, and returns
 * them all in a list in increasing order of  (day, hour, min).  Returns
 * an empty list if there are no such records. 
 * The  records  in the returned list should not be freed, but it is the
 * caller's responsibility to free the list itself.
 * The time complexity of this function must be O(log n + m), where m is
 * the length of the returned list.
 * You MUST use the AVLTree ADT (from Task 1) in your implementation.
 */
List     DbFindByFlightNumber(FlightDb db, char *flightNumber) {
	Record dummy1 = RecordNew(flightNumber, "", "", 0, 0, 0, 0); // Lower bound
	Record dummy2 = RecordNew(flightNumber, "", "", 6, 23, 59, 0); // Upper bound
	// Search for results
    List l = TreeSearchBetween(db->byFlightNumber, dummy1, dummy2);
    // Free dummy records
    RecordFree(dummy1);
    RecordFree(dummy2);
	return l;
}

/**
 * Searches  for all records with the given departure airport and day of
 * week (0 to 6), and returns them all in a list in increasing order  of
 * (hour, min, flight number).
 * Returns an empty list if there are no such records.
 * The  records  in the returned list should not be freed, but it is the
 * caller's responsibility to free the list itself.
 * The time complexity of this function must be O(log n + m), where m is
 * the length of the returned list.
 * You MUST use the AVLTree ADT (from Task 1) in your implementation.
 */
List     DbFindByDepartureAirportDay(FlightDb db, char *departureAirport,
                                     int day) {
	Record dummy1 = RecordNew("", departureAirport, "", day, 0, 0, 0); // Lower bound
	Record dummy2 = RecordNew("", departureAirport, "", day, 23, 59, 0); // Upper bound
	// Search for results
    List l = TreeSearchBetween(db->byAirportDay, dummy1, dummy2);
    // Free dummy records
    RecordFree(dummy1);
    RecordFree(dummy2);
	return l;
}

/**
 * Searches  for  all  records  between  (day1, hour1, min1)  and (day2,
 * hour2, min2), and returns them all in a list in increasing  order  of
 * (day, hour, min, flight number).
 * Returns an empty list if there are no such records.
 * The  records  in the returned list should not be freed, but it is the
 * caller's responsibility to free the list itself.
 * The time complexity of this function must be O(log n + m), where m is
 * the length of the returned list.
 * You MUST use the AVLTree ADT (from Task 1) in your implementation.
 */
List     DbFindBetweenTimes(FlightDb db, 
                            int day1, int hour1, int min1, 
                            int day2, int hour2, int min2) {

	Record dummy1 = RecordNew("", "", "", day1, hour1, min1, 0); // Lower bound
	Record dummy2 = RecordNew("zzzzzzzz", "", "", day2, hour2, min2, 0); // Upper bound
	// Search for results
    List l = TreeSearchBetween(db->byTime, dummy1, dummy2);
    // Free dummy records
    RecordFree(dummy1);
    RecordFree(dummy2);
	return l;
}

/**
 * Searches  for  and  returns  the  earliest next flight from the given
 * departure airport, on or after the given (day, hour, min).
 * The returned record must not be freed or modified. 
 * The time complexity of this function must be O(log n).
 * You MUST use the AVLTree ADT (from Task 1) in your implementation.
 */
Record   DbFindNextFlight(FlightDb db, char *departureAirport, 
                          int day, int hour, int min) {
	Record dummy1 = RecordNew("", departureAirport, "", day, hour, min, 0);
	Record dummysmall = RecordNew("", departureAirport, "", 0, 0, 0, 0);
    // Search for result	
	Record r = TreeNext(db->byAirportDay, dummy1);
	// If nothing found, wrap back around to beginning of week
	if(r == NULL) {
	    r = TreeNext(db->byAirportDay, dummysmall);
	}
	// Free dummy record
	RecordFree(dummy1);
	RecordFree(dummysmall);
	return r;
}

