<h3 align="left">ProvaFinale_AlgoritmiEStruttureDati_2022-2023</h3>

###

<p align="left">This project focuses on planning the most efficient travel route along a highway modeled as a sequence of service stations. Each station is uniquely identified by its distance from the highway's start, expressed as a non-negative integer.<br><br>Each service station has a fleet of electric rental vehicles. A vehicle's range is specified by a positive integer (in km). By renting a car from a station s, you can reach any station t as long as the distance between s and t is less than or equal to the car's range. Travel is always unidirectional, moving from a station at a shorter distance to one at a greater distance.<br><br>The primary objective is to find a route with the minimum number of stops between a given starting and ending station. In cases where multiple paths have the same minimum number of stops, the tie-breaking rule is to choose the path that, when compared step-by-step from the end backwards, has the shortest distance for the first differing stop.<br><br>For example, the correct path from station 20 to 50 is 20 → 30 → 50, not 20 → 45 → 50, because at the second-to-last stop, 30 is closer to the start than 45.</p>

###

<h4 align="left">Input File Format and Commands</h4>

###

<p align="left">The program processes a text file containing a sequence of commands, one per line.<br><br>· aggiungi-stazione distance num-cars range-1 ... range-n:<br>Adds a new service station with a specified distance and a fleet of vehicles.<br>Expected Output: aggiunta or non aggiunta.<br><br>· demolisci-stazione distance:<br>Removes the station at the specified distance.<br>Expected Output: demolita or non demolita.<br><br>· aggiungi-auto station-distance car-range-to-add:<br>Adds a new car to an existing station.<br>Expected Output: aggiunta or non aggiunta.<br><br>· rottama-auto station-distance car-range-to-scrap:<br>Removes a car from a station.<br>Expected Output: rottamata or non rottamata.<br><br>· pianifica-percorso start-distance end-distance:<br>Plans the optimal path based on the specified criteria.<br>Expected Output: A single line with the distances of the stations in the path, separated by spaces (e.g., 20 30 50), or nessun percorso if no path exists. The starting and ending stations are guaranteed to exist.</p>

###
