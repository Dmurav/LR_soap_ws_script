Action()
{
	
	// instantiate names of ouput files
	char* city_file = "C:\\Users\\serge\\Desktop\\LR_scripts\\cities.txt";
	char* file = "C:\\Users\\serge\\Desktop\\LR_scripts\\wether.txt";
	// instantiate counter
	int count;
	
	// Get list of City and coordinates only one times
	if (count == 0) {
		
		lr_start_transaction("Get list of city");	
		// Get SOAP response with list of Cities and coordinates
		getListOfCity();
		// Process response to XML
		processResultCitiesXML();
		// Get strings with cities and coordinates by xpath
		getCityAndCoordinates();
		// write cities and coordinates to file
		writeCitiesToFile(city_file);
		lr_end_transaction("Get list of city", LR_AUTO);
		// increment counter
		count ++;
	
	} else {
		
		lr_start_transaction("Get wether parametrs");
		// Get SOAP response by coordinates
		getWetherParametrsByCity();
		// Process response to XML
		processResultWetherXML();
		// Get wether parametrs from XML by xpath
		getWetherParametrs();
		// Print parametrs to console
		printWetherParametrsToConsole();
		// Print parametrs to file
		writeParametrsToFile(file);
		lr_end_transaction("Get wether parametrs", LR_AUTO);
		
	}
	
 	return 0;
}

