# FlightDb
<html hola_ext_inject="disabled"><head>
	<meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
	<title>COMP2521 21T1 - Assignment 1</title>
<!--

<link rel="stylesheet" type="text/css" href="course.css"><style id="style-1-cropbar-clipper">
.en-markup-crop-options {
    top: 18px !important;
    left: 50% !important;
    margin-left: -100px !important;
    width: 200px !important;
    border: 2px rgba(255,255,255,.38) solid !important;
    border-radius: 4px !important;
}

.en-markup-crop-options div div:first-of-type {
    margin-left: 0px !important;
}
</style>
-->

	<style>
		body {
			font-family: arial, sans-serif;
			font-size: 11pt;
			margin: 10px 20px;
			margin-left:60px;
			max-width: 900px;
		}
		
		a {
			color: #4444CC;
			text-decoration: none;
		}
		
		a.active {
			color:#4444CC;
			text-decoration: none;
		}
		
		a.inactive {
			color: #BBBBDD;
			text-decoration: none;
		}
		
		a[href]:hover {
			color: #CC0000;
			background: #FFFFCC;
		}
		
		small {
			font-size: 75%
		}
		
		pre {
			background: #EEEEFF;
			border: thin solid #9999CC;
			margin: 5px 20px 5px 20px;
			padding: 4px 8px;
		}
		
		tt {
			color: #107F80;
			font-size: 1.0em;
		}
		
		span.toggle {
			font-size: 67%;
		}
		
		span.notice {
			font-size: 110%;
		}
		
		span.tiny {
			font-size: 75%;
			font-weight: normal;
		}
		
		span.heading {
			font-size: 18pt;
			color: #4444CC;
		}
		
		span.subheading {
			font-size: 16pt;
			color: #000000;
			font-weight: normal;
		}
		
		span.marks {font-weight:normal;font-size:75%;}
		span.identifier {color:#993300;font-size:110%;font-weight:bold;font-family:courier;}
		span.contentLink {font-weight:bold;font-size:110%}
		span.contentNote {font-weight:normal;font-size:85%;}
		tr.heading {font-size:large;font-weight:bold;background-color:#DDAA77;}
		table.note {border:thin solid black;padding:2pt;width:75%}
		div.note {border:thin solid black;font-size:90%;margin:5px 60px 5px 60px;padding:4px 8px;}
		dt {margin-top: 10px;}
		dt.item {font-weight:bold;}
		h2 {font-size:16pt;font-weight:300;color:#4444CC;}
		h3 {font-size:14pt;font-weight:300;color:#4444CC;}
		.h2tt {font-size:17pt;font-weight:300;color:#4444CC;font-family:courier;}
		.h3tt {font-size:15pt;font-weight:300;color:#4444CC;font-family:courier;}
		.red {color:#CC0000;}
		.green {color:#006600;}
		.brown {color:#993300;}
		.grey {color:#AAAAAA;}
		.comment {font-size:90%;color:#666666}
		.important {font-weight:bold;color:#CC0000;}
		.bigQ {font-size:13pt;font-style:italic;}
		dd{color:rgb(86, 86, 86)} 

		 span.v2 {background-color:palegoldenrod; color:darkgreen}
		 span.v3 {background-color:lightcyan; color:darkgreen}
		 span.v4 {background-color:lightgreen; color:darkgreen}
		 span.mystrike{ text-decoration: line-through; color:grey; }

		li:not(:last-child) {
			margin-bottom: 5px;
		}
	}
	</style>
</head>

<body style="text-align: justify;">
<div align="center">
	<h2><span style="font-size: 18pt">COMP2521: Assignment 1</span></h2>
	<h2><span style="font-size: 22pt">ADTs: FlightDb Using a <i>Generic</i> AVL Tree </span></h2>
</div>

<p>This specification may change! So please check the following change log frequently.</p>

<h3 style="color:green;">Change log:</h3>
<ul>
	<li>[11/03 12:50pm] Fixed style inconsistencies</li>
	<li>[12/03 11:20pm] Fixed inconsistent function names between <code>Record.c</code> and <code>Record.h</code></li>
	<li>[13/03 07:40pm] Fixed <code>n-&gt;height</code> not being initialised in <code>newNode</code> in <code>AVLTree.c</code></li>
	<li>[18/03 04:40pm] Added comments to <code>TreeNext</code> and <code>DbFindNextFlight</code> to clarify what should be returned if there is no appropriate record</li>
	<li>[18/03 04:50pm] Added sample tests</li>
	<li>[26/03 03:00pm] Added clarifications</li>
	<li>[30/03 12:55am] Added instructions on how to Submit this assignment 
	(goto: <a href="#Submission">Submission</a>)</li>	
</ul>

<hr>

<h2>Objectives</h2>
<ul>
	<li>to give you experience in implementing ADTs in C</li>
	<li>to give you experience with higher order functions and generic ADTs</li>
	<li>to give you further practice with C and data structures</li>
</ul>

<h2>Admin</h2>
<div>
	<ul>
		<li><p><b>Marks:</b> 15 marks</p></li>
		<li><p><b>Deadline:</b> 5pm <strike>Friday</strike> Saturday of Week 07</p></li>
		<li><p><b>Late Penalty:</b> 1.5 marks per day off the ceiling. For example, if you submit any time between 1 and 2 days late, the maximum mark you can obtain is 12/15. The latest you can submit is 5pm Monday of Week 08. After this date, you will receive zero for the assignment.</p></li>
		<li><p><b>Individual Assignment:</b> This assignment is completed individually.</p></li>
	</ul>
</div>

<h2>Aim</h2>

<p>In this assignment, your task is to implement functions for the AVLTree and FlightDb ADTs, in the files <code>AVLTree.c</code> and <code>FlightDb.c</code>. You will have to write wrapper code to test your implementations, and make sure to test a variety of conditions.</p>

<p>Please note that, you need to submit only the C code implementing the required functions in the files <code>AVLTree.c</code> and <code>FlightDb.c</code>.</p>

<h3>Week 04 Lab</h3>

<p>You should first complete the Week 04 lab exercise. This assignment is based on many concepts discussed in the Week 04 lab, like comparison functions, function pointers and their usage in implementing Tree and StudentDb ADTs. In this assignment, you need to use similar setup, however here you need to implement the AVLTree and FlightDb ADTs.</p>

<hr>

<h2>Clarifications</h2>
<ul>
	<li>You can assume that flights with the same flight number will <b>always</b> have the same departure and arrival airports. You do not need to check this in your code.</li>
	<li>You are always allowed to use helper functions. Since you are not allowed to modify anything above "the line" in <code>AVLTree.c</code>, please put the prototypes for your helper functions under this line.</li>
	<li>You may not use <code>string.h</code> in <code>AVLTree.c</code>. Doing this is a sign that your code is incorrect.</li>
	<li>For <code>DbFindBetweenTimes</code>, the times are <i>inclusive</i>.</li>
	<li>For <code>DbFindBetweenTimes</code>, you will never be passed two times where the first time is later than the second.</li>
	<li>For <code>DbFindNextFlight</code>, if there are multiple flights that occur at the same time that could be selected from, then you must take the one with the smallest flight number.</li>
</ul>

<hr>

<h2>Task 1: AVLTree ADT</h2>
<p>The AVLTree ADT implements an AVL tree of records with a custom comparison function.</p>
<p>You need to implement the following <b>three functions</b> in the file <code>AVLTree.c</code>.</p>

<!-- HTML generated using hilite.me -->
<div style="background: #ffffff; overflow: auto; width: auto; border: solid gray; border-width: .1em .1em .1em .8em; padding: .2em .6em;">
<pre style="margin: 0; line-height: 125%"><span style="color: #888888">/**</span>
<span style="color: #888888"> * Inserts the given record into the AVL tree.</span>
<span style="color: #888888"> * You  must use the proper AVL insertion algorithm, as discussed in the</span>
<span style="color: #888888"> * lectures.</span>
<span style="color: #888888"> * The time complexity of this function must be O(log n).</span>
<span style="color: #888888"> * Returns true if the record was inserted  successfully,  or  false  if</span>
<span style="color: #888888"> * there was already a record that compares equal to the given record in</span>
<span style="color: #888888"> * the tree (according to the comparison function).</span>
<span style="color: #888888"> */</span>
<span style="color: #333399; font-weight: bold">bool</span>   <span style="color: #0066BB; font-weight: bold">TreeInsert</span>(Tree t, Record rec);

<span style="color: #888888">/**</span>
<span style="color: #888888"> * Searches  for  all  records  between the two given records, inclusive</span>
<span style="color: #888888"> * (according to the comparison function) and returns the records  in  a</span>
<span style="color: #888888"> * list  in  order.  Returns an empty list if there are no such records.</span>
<span style="color: #888888"> * Assumes that `lower` is less than `upper`.</span>
<span style="color: #888888"> * The time complexity of this function must be O(log n + m), where m is</span>
<span style="color: #888888"> * the length of the returned list.</span>
<span style="color: #888888"> */</span>
List   <span style="color: #0066BB; font-weight: bold">TreeSearchBetween</span>(Tree t, Record lower, Record upper);

<span style="color: #888888">/**</span>
<span style="color: #888888"> * Returns the smallest record greater than or equal to the given record</span>
<span style="color: #888888"> * r (according to the comparison function), or NULL if there is no such</span>
<span style="color: #888888"> * record.</span>
<span style="color: #888888"> * The time complexity of this function must be O(log n).</span>
<span style="color: #888888"> */</span>
Record <span style="color: #0066BB; font-weight: bold">TreeNext</span>(Tree t, Record r);
</pre>
</div>

<!--
<pre>
/**
 * Inserts the given record into the AVL tree.
 * You  must use the proper AVL insertion algorithm, as discussed in the
 * lectures.
 * The time complexity of this function must be O(log n).
 * Returns true if the record was inserted  successfully,  or  false  if
 * there was already a record that compares equal to the given record in
 * the tree (according to the comparison function).
 */
bool   TreeInsert(Tree t, Record rec);

/**
 * Searches  for  all  records  between the two given records, inclusive
 * (according to the comparison function) and returns the records  in  a
 * list  in  order.  Returns an empty list if there are no such records.
 * Assumes that `lower` is less than `upper`.
 * The time complexity of this function must be O(log n + m), where m is
 * the length of the returned list.
 */
List   TreeSearchBetween(Tree t, Record lower, Record upper);

/**
 * Returns the smallest record greater than or equal to the given record
 * r (according to the comparison function), or NULL if there is no such
 * record.
 * The time complexity of this function must be O(log n).
 */
Record TreeNext( Tree t, Record r);
</pre>
-->

<p>Please make sure you follow the following instructions:

</p><ul>
	<li>You must use the the proper AVL insertion algorithm, as discussed in the lectures, for inserting a record.</li>
	<li>Do <b>not modify</b> <code>AVLTree.h</code>. You will only submit <code>AVLTree.c</code> for this task.</li>
	<li>In <code>AVLTree.c</code>, do <b>not modify</b> the structures defined for '<code>node</code>' and '<code>tree</code>'.</li>
	<li>You must <b>not modify</b> the provided functions in AVLTree.c (from line 1 to 100).</li>
</ul>

<hr>

<h2>Task 2: FlightDb ADT</h2>
<p>FlightDb ADT stores flight details (see <code>Record.h</code> and <code>Record.c</code> for more information), and offers efficient operations for the searching tasks defined in the interface <code>FlightDb.h</code>. Your task is to implement the interface <code>FlightDb.h</code> in the file <code>FlightDb.c</code>. You MUST use the AVLTree ADT (from Task 1) in your implementation. You MUST only create one record per flight, like you did in Week-04 lab.</p>

<p>In this assignment, our focus is on learning how to implement an efficient database ADT using an AVL tree ADT. So we assume the following regarding the flight details:</p>
<ul>
	<li>flight schedule is the same every week</li>
	<li>departureDay is between 0 and 6. 0 for Monday, 1 for Tuesday, ... , 6 for Sunday</li>
	<li>departureHour is between 0 and 23 (inclusive)</li>
	<li>departureMinute is between 0 to 59 (inclusive)</li>
	<li>durationMinutes indicates the duration of the flight in minutes</li>
</ul>    

<p>Please do NOT modify the header file <code>FlightDb.h</code>, you will only submit <code>FlightDb.c</code> for this task. We will test your implementation using our test sets, so make sure you do NOT modify function headers (signatures) in the header file <code>FlightDb.h</code>.</p>

<p>You need to implement the following functions in <code>FlightDb.c</code>.</p>

<!-- HTML generated using hilite.me -->
<div style="background: #ffffff; overflow: auto; width: auto; border: solid gray; border-width: .1em .1em .1em .8em; padding: .2em .6em;">
<pre style="margin: 0; line-height: 125%"><span style="color: #888888">/**</span>
<span style="color: #888888"> * Creates a new flight DB.</span>
<span style="color: #888888"> * You MUST use the AVLTree ADT (from Task 1) in your implementation.</span>
<span style="color: #888888"> */</span>
FlightDb <span style="color: #0066BB; font-weight: bold">DbNew</span>(<span style="color: #333399; font-weight: bold">void</span>);

<span style="color: #888888">/**</span>
<span style="color: #888888"> * Frees all memory allocated to the given flight DB</span>
<span style="color: #888888"> */</span>
<span style="color: #333399; font-weight: bold">void</span>     <span style="color: #0066BB; font-weight: bold">DbFree</span>(FlightDb db);

<span style="color: #888888">/**</span>
<span style="color: #888888"> * Inserts  a  flight  record  into the given DB if there is not already</span>
<span style="color: #888888"> * record with the same flight number, departure airport, day, hour  and</span>
<span style="color: #888888"> * minute.</span>
<span style="color: #888888"> * If  inserted successfully, this function takes ownership of the given</span>
<span style="color: #888888"> * record (so the caller should not modify or free it).</span>
<span style="color: #888888"> * Returns true if the record was successfully inserted,  and  false  if</span>
<span style="color: #888888"> * the  DB  already  contained  a  record  with  the same flight number,</span>
<span style="color: #888888"> * departure airport, day, hour and minute.</span>
<span style="color: #888888"> * The time complexity of this function must be O(log n).</span>
<span style="color: #888888"> * You MUST use the AVLTree ADT (from Task 1) in your implementation.</span>
<span style="color: #888888"> */</span>
<span style="color: #333399; font-weight: bold">bool</span>     <span style="color: #0066BB; font-weight: bold">DbInsertRecord</span>(FlightDb db, Record r);

<span style="color: #888888">/**</span>
<span style="color: #888888"> * Searches  for  all  records with the given flight number, and returns</span>
<span style="color: #888888"> * them all in a list in increasing order of  (day, hour, min).  Returns</span>
<span style="color: #888888"> * an empty list if there are no such records.</span>
<span style="color: #888888"> * The  records  in the returned list should not be freed, but it is the</span>
<span style="color: #888888"> * caller's responsibility to free the list itself.</span>
<span style="color: #888888"> * The time complexity of this function must be O(log n + m), where m is</span>
<span style="color: #888888"> * the length of the returned list.</span>
<span style="color: #888888"> * You MUST use the AVLTree ADT (from Task 1) in your implementation.</span>
<span style="color: #888888"> */</span>
List     <span style="color: #0066BB; font-weight: bold">DbFindByFlightNumber</span>(FlightDb db, <span style="color: #333399; font-weight: bold">char</span> <span style="color: #333333">*</span>flightNumber);

<span style="color: #888888">/**</span>
<span style="color: #888888"> * Searches  for all records with the given departure airport and day of</span>
<span style="color: #888888"> * week (0 to 6), and returns them all in a list in increasing order  of</span>
<span style="color: #888888"> * (hour, min, flight number).</span>
<span style="color: #888888"> * Returns an empty list if there are no such records.</span>
<span style="color: #888888"> * The  records  in the returned list should not be freed, but it is the</span>
<span style="color: #888888"> * caller's responsibility to free the list itself.</span>
<span style="color: #888888"> * The time complexity of this function must be O(log n + m), where m is</span>
<span style="color: #888888"> * the length of the returned list.</span>
<span style="color: #888888"> * You MUST use the AVLTree ADT (from Task 1) in your implementation.</span>
<span style="color: #888888"> */</span>
List     <span style="color: #0066BB; font-weight: bold">DbFindByDepartureAirportDay</span>(FlightDb db, <span style="color: #333399; font-weight: bold">char</span> <span style="color: #333333">*</span>departureAirport,
                                     <span style="color: #333399; font-weight: bold">int</span> day);

<span style="color: #888888">/**</span>
<span style="color: #888888"> * Searches  for  all  records  between  (day1, hour1, min1)  and (day2,</span>
<span style="color: #888888"> * hour2, min2), and returns them all in a list in increasing  order  of</span>
<span style="color: #888888"> * (day, hour, min, flight number).</span>
<span style="color: #888888"> * Returns an empty list if there are no such records.</span>
<span style="color: #888888"> * The  records  in the returned list should not be freed, but it is the</span>
<span style="color: #888888"> * caller's responsibility to free the list itself.</span>
<span style="color: #888888"> * The time complexity of this function must be O(log n + m), where m is</span>
<span style="color: #888888"> * the length of the returned list.</span>
<span style="color: #888888"> * You MUST use the AVLTree ADT (from Task 1) in your implementation.</span>
<span style="color: #888888"> */</span>
List     <span style="color: #0066BB; font-weight: bold">DbFindBetweenTimes</span>(FlightDb db, 
                            <span style="color: #333399; font-weight: bold">int</span> day1, <span style="color: #333399; font-weight: bold">int</span> hour1, <span style="color: #333399; font-weight: bold">int</span> min1, 
                            <span style="color: #333399; font-weight: bold">int</span> day2, <span style="color: #333399; font-weight: bold">int</span> hour2, <span style="color: #333399; font-weight: bold">int</span> min2);

<span style="color: #888888">/**</span>
<span style="color: #888888"> * Searches  for  and  returns  the  earliest next flight from the given</span>
<span style="color: #888888"> * departure airport, on or after the given (day, hour, min), or NULL if</span>
<span style="color: #888888"> * there is no such flight.</span>
<span style="color: #888888"> * The returned record must not be freed or modified.</span>
<span style="color: #888888"> * The time complexity of this function must be O(log n).</span>
<span style="color: #888888"> * You MUST use the AVLTree ADT (from Task 1) in your implementation.</span>
<span style="color: #888888"> */</span>
Record   <span style="color: #0066BB; font-weight: bold">DbFindNextFlight</span>(FlightDb db, <span style="color: #333399; font-weight: bold">char</span> <span style="color: #333333">*</span>departureAirport, 
                          <span style="color: #333399; font-weight: bold">int</span> day, <span style="color: #333399; font-weight: bold">int</span> hour, <span style="color: #333399; font-weight: bold">int</span> min);
</pre>
</div>

<!--
<pre>
/**
 * Creates a new flight DB.
 * You MUST use the AVLTree ADT (from Task 1) in your implementation.
 */
FlightDb DbNew(void);

/**
 * Frees all memory allocated to the given flight DB
 */
void     DbFree(FlightDb db);

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
bool     DbInsertRecord(FlightDb db, Record r);

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
List     DbFindByFlightNumber(FlightDb db, char *flightNumber);

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
                                     int day);


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
                            int day2, int hour2, int min2);


/**
 * Searches  for  and  returns  the  earliest next flight from the given
 * departure airport, on or after the given (day, hour, min), or NULL if
 * there is no such flight.
 * The returned record must not be freed or modified. 
 * The time complexity of this function must be O(log n).
 * You MUST use the AVLTree ADT (from Task 1) in your implementation.
 */
Record   DbFindNextFlight(FlightDb db, char *departureAirport, 
                          int day, int hour, int min);
</pre>
-->

<hr>

<h2>Setting Up</h2>
<p>Create a directory for this assignment, change into it, and run the following command:</p>

<pre>unzip <a href="./downloads/ass1.zip">/web/cs2521/21T1/assigns/ass1/downloads/ass1.zip</a>
</pre>

<p>If you're working at home, download ass1.zip by clicking on the above link and then run the unzip command on the downloaded file.</p>
<p>If you've done the above correctly, you should now have the following files:</p>

<dl class="dl-horizontal">
	<dt><code>List.c</code></dt>
	<dd>implementation of the <code>List</code> ADT (complete)</dd>

	<dt><code>List.h</code></dt>
	<dd>interface to the <code>List</code> ADT</dd>

	<dt><code>Record.c</code></dt>
	<dd>implementation of the <code>Record</code> ADT (complete)</dd>

	<dt><code>Record.h</code></dt>
	<dd>interface to the <code>Record</code> ADT</dd>

	<dt><code>FlightDb.c</code></dt>
	<dd>implementation of the <code>FlightDb</code> ADT (incomplete)</dd>

	<dt><code>FlightDb.h</code></dt>
	<dd>interface to the <code>FlightDb</code> ADT</dd>

	<dt><code>AVLTree.c</code></dt>
	<dd>implementation of the <code>AVLTree</code> ADT (incomplete)</dd>

	<dt><code>AVLTree.h</code></dt>
	<dd>interface to the <code>Tree</code> ADT</dd>
</dl>

<hr>

<h2>Testing</h2>
<p>You can download the sample tests by running the following command from your assignment directory.</p>

<p><b>Important:</b> The test files provide new versions of <code>Record.c</code> and <code>Makefile</code>. If you made changes to any of these files, you should create backups of these first.</p>

<pre>unzip <a href="./downloads/testing.zip">/web/cs2521/21T1/assigns/ass1/downloads/testing.zip</a>
</pre>

<p>If you're working at home, download testing.zip by clicking on the above link and then run the unzip command on the downloaded file.</p>

<p>You should now have the following <i>new</i> files:</p>
<dl class="dl-horizontal">
	<dt><code>testAss1.c</code></dt>
	<dd>a program that contains some sample tests</dd>

	<dt><code>output/</code></dt>
	<dd>a directory containing expected output for the tests in <code>testAss1.c</code></dd>
</dl>

<p>To test your implementation, run the <code>make</code> command to compile your code and then run <code>./testAss1 <i>test-number</i></code> (for example, <code>./testAss1 1</code>). Then compare the output to the expected output in the <code>output/</code> directory. The expected output for test <i>n</i> is in <code>output/<i>n</i>.exp</code>.</p>

<p>Please note that the sample tests are by no means comprehensive - you should do your own testing by adding tests to this file. To avoid modifying the existing tests, you should create functions containing your tests, and extend the switch statement in the <code>main</code> function to call these functions. Of course, there won't be any expected output for these tests so you will need to inspect the output yourself.</p>

<p>The sample tests also do not directly test the AVLTree ADT implementation. However, it is possible to test your AVLTree by creating a tree (you'll need to create a comparison function first), inserting records and then calling the various AVLTree ADT functions.</p>

<hr>

<h2>Assessment Criteria</h2>

<p>Your program will be tested thoroughly and objectively. This assignment will be marked out of 15 where 12 marks are for correctness and 3 marks are for your solution's complexity, style and comments. Task 1 is worth 5 marks and Task 2 is worth 10 marks.</p>

<hr>

<a name="Submission"></a>
<h2>Submission</h2>

<p>You need to submit two files: <code><b>AVLTree.c</b></code> and <code><b>FlightDb.c</b></code>.</p>

<!--
<p>Later, instructions on how to submit will be posted here.</p>
-->

<p>To Submit this assignment, go to the <b><a target="_blank" href="https://webcms3.cse.unsw.edu.au/COMP2521/21T1/resources/57618">Submission page</a></b> and click the tab named "<b>Make Submission</b>".</p> 


<p> You can also submit at the command-line, by running
</p><pre><b>give cs2521 ass1 AVLTree.c FlightDb.c </b></pre>
<p>

</p><hr>

<h2>Plagiarism</h2>

<p>This is an individual assignment. Each student will have to develop their own solution without help from other people. You are not permitted to exchange code or pseudocode. If you have questions about the assignment, ask your tutor. All work submitted for assessment must be entirely your own work. We regard unacknowledged copying of material, in whole or part, as an extremely serious offence. For further information, read the <a href="https://cgi.cse.unsw.edu.au/~cs2521/21T1/admin/outline/index.php#conduct" target="_blank">Student Conduct</a>.</p>
  
<hr>




</body></html>
