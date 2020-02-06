#ifndef _FUNCTIONS
#define _FUNCTIONS

// Функция для записи в файл
writeFile(char* file, char* param1, char* param2, char* param3, char* param4, char* param5, char* param6)
{
	// Инициируем переменную файл
    int fp;
    // Открываем файл для добавления данных
    fp=fopen(file,"a+");   
   	
    // Записываем строку - param1:param2 c переходом на новую строку\n
    fputs(param1,fp);
    fputs(",",fp);
    fputs(param2,fp);
    fputs(",",fp);
    fputs(param3,fp);
    fputs(",",fp);
    fputs(param4,fp);
    fputs(",",fp);
    fputs(param5,fp);
    fputs(",",fp);
    fputs(param6,fp);
    fputs("\n",fp);
    
    // Закрываем файл
    fclose(fp);

    return 0;   
}

// Функция для записи городов в файл
writeCitiesToFile(char* file)
{
	char* param1 = lr_eval_string("{cities}");
	char* param2 = lr_eval_string("{coordinates}");	
	// Инициируем переменную файл
    int fp;
    // Открываем файл для добавления данных
    fp=fopen(file,"a+");   
   	
    // Записываем строку - param1:param2 c переходом на новую строку\n
    fputs(param1,fp);
    fputs("\n",fp);
    fputs(param2,fp);
   
    // Закрываем файл
    fclose(fp);

    return 0;   
}

// Функция позволяет провести замену подстрок в тексте
// Первый аргумент - сам текст, второй - старые символы, третий - новые символы
char* replaceWord(const char *s, const char *oldW, const char *newW)
{ 
	char *result;
    int i, cnt = 0; 
    int newWlen = strlen(newW); 
    int oldWlen = strlen(oldW); 
  
    // Counting the number of times old word 
    // occur in the string 
    for (i = 0; s[i] != '\0'; i++) 
    { 
        if (strstr(&s[i], oldW) == &s[i]) 
        { 
            cnt++; 
  
            // Jumping to index after the old word. 
            i += oldWlen - 1; 
        } 
    } 
  
    // Making new string of enough length 
    result = (char *)malloc(i + cnt * (newWlen - oldWlen) + 1); 
  
    i = 0; 
    while (*s) 
    { 
        // compare the substring with the result 
        if (strstr(s, oldW) == s) 
        { 
            strcpy(&result[i], newW); 
            i += newWlen; 
            s += oldWlen; 
        } 
        else
            result[i++] = *s++; 
    } 
  
    result[i] = '\0'; 
    return result; 
}

// Функция для получения SOAP ответа со списком городов
void getListOfCity(){
	// Get list of cityes with coordinates
	web_service_call( "StepName=Cities",
		"SOAPMethod=ndfdXML|ndfdXMLPort|LatLonListCityNames",
		"ResponseParam=response",
		"Service=ndfdXML",
		"ExpectedResponse=SoapResult",
		"Snapshot=t1580731582.inf",
		BEGIN_ARGUMENTS,
		"displayLevel=1",
		END_ARGUMENTS,
		BEGIN_RESULT,
		"listCityNamesOut=Param_listCityNamesOut",
		END_RESULT,
		LAST);
}

// Функция для получения SOAP ответа со списком параметров по городу
void getWetherParametrsByCity(){
		// Get wether paranetrs by random city
	web_service_call( "StepName=NDFDgen_101",
		"SOAPMethod=ndfdXML|ndfdXMLPort|NDFDgen",
		"ResponseParam=response",
		"Service=ndfdXML",
		"ExpectedResponse=SoapResult",
		"Snapshot=t1580741915.inf",
		BEGIN_ARGUMENTS,
		"latitude={latitude}",
		"longitude={longitude}",
		"product=time-series",
		"startTime=2020-02-07T11:00",
		"endTime=2020-02-07T12:00",
		"Unit=",
		"xml:weatherParameters="
			"<weatherParameters>"
				"<maxt>TRUE</maxt>"
				"<mint>TRUE</mint>"
				"<temp></temp>"
				"<dew>TRUE</dew>"
				"<pop12></pop12>"
				"<qpf></qpf>"
				"<sky></sky>"
				"<snow></snow>"
				"<wspd>TRUE</wspd>"
				"<wdir></wdir>"
				"<wx></wx>"
				"<waveh></waveh>"
				"<icons></icons>"
				"<rh>TRUE</rh>"
				"<appt></appt>"
				"<incw34></incw34>"
				"<incw50></incw50>"
				"<incw64></incw64>"
				"<cumw34></cumw34>"
				"<cumw50></cumw50>"
				"<cumw64></cumw64>"
				"<critfireo></critfireo>"
				"<dryfireo></dryfireo>"
				"<conhazo></conhazo>"
				"<ptornado></ptornado>"
				"<phail></phail>"
				"<ptstmwinds></ptstmwinds>"
				"<pxtornado></pxtornado>"
				"<pxhail></pxhail>"
				"<pxtstmwinds></pxtstmwinds>"
				"<ptotsvrtstm></ptotsvrtstm>"
				"<pxtotsvrtstm></pxtotsvrtstm>"
				"<tmpabv14d></tmpabv14d>"
				"<tmpblw14d></tmpblw14d>"
				"<tmpabv30d></tmpabv30d>"
				"<tmpblw30d></tmpblw30d>"
				"<tmpabv90d></tmpabv90d>"
				"<tmpblw90d></tmpblw90d>"
				"<prcpabv14d></prcpabv14d>"
				"<prcpblw14d></prcpblw14d>"
				"<prcpabv30d></prcpabv30d>"
				"<prcpblw30d></prcpblw30d>"
				"<prcpabv90d></prcpabv90d>"
				"<prcpblw90d></prcpblw90d>"
				"<precipa_r></precipa_r>"
				"<sky_r></sky_r>"
				"<td_r></td_r>"
				"<temp_r></temp_r>"
				"<wdir_r></wdir_r>"
				"<wspd_r></wspd_r>"
				"<wwa></wwa>"
				"<tstmprb></tstmprb>"
				"<tstmcat></tstmcat>"
				"<wgust></wgust>"
				"<iceaccum></iceaccum>"
				"<maxrh></maxrh>"
				"<minrh></minrh>"
			"</weatherParameters>",
		END_ARGUMENTS,
		BEGIN_RESULT,
		END_RESULT,
		LAST);
}

// Обработка SOAP ответа в нормальный XML
void processResultCitiesXML(){
	
	char *text;
	char* old1 = "&lt;";
	char* new1 = "<";
	char* old2 = "&gt;";
	char* new2 = ">";
	char *resultCity;
	
	lr_xml_extract("XML={response}",
	               "Query=/SOAP-ENV:Envelope/SOAP-ENV:Body/ns1:LatLonListCityNamesResponse/listLatLonOut/text()[1]",
	               "XMLFragmentParam=ResultCity",
	               LAST);
	
	
	text = lr_eval_string("{ResultCity}");
	resultCity = replaceWord(text, old1, new1);
	resultCity = replaceWord(resultCity, old2, new2);
	lr_save_string(resultCity, "lr_resultCity");
	
}

// Получение строк с городами и координатами из XML
void getCityAndCoordinates(){
	
	lr_xml_extract("XML={lr_resultCity}",
	               "Query=/dwml/latLonList/text()",
	               "XMLFragmentParam=coordinates",
	               "NotFound=continue",
	               LAST);
	
	lr_xml_extract("XML={lr_resultCity}",
	               "Query=/dwml/cityNameList/text()",
	               "XMLFragmentParam=cities",
	               "NotFound=continue",
	               LAST);
}

// Обработка SOAP ответа и получение XML с параметрами погоды
void processResultWetherXML(){
	
	char *res;
	char* old1 = "&lt;";
	char* new1 = "<";
	char* old2 = "&gt;";
	char* new2 = ">";
	char *replaced;
	
	lr_xml_extract("XML={response}",
	               "Query=/SOAP-ENV:Envelope/SOAP-ENV:Body/ns1:NDFDgenResponse/dwmlOut/text()",
	               "XMLFragmentParam=Result",
	               LAST);
	
	
	res = lr_eval_string("{Result}");
	replaced = replaceWord(res, old1, new1);
	replaced = replaceWord(replaced, old2, new2);
	lr_save_string(replaced, "AnotherResult");
	
}

// Получение параметров погоды из XML
void getWetherParametrs(){
	
	lr_xml_extract("XML={AnotherResult}",
	               "Query=/dwml/data/parameters/temperature[1]/value/text()",
	               "XMLFragmentParam=maxTemp",
	               "NotFound=continue",
	               LAST);
	
	lr_xml_extract("XML={AnotherResult}",
	               "Query=/dwml/data/parameters/temperature[2]/value/text()",
	               "XMLFragmentParam=minTemp",
	               "NotFound=continue",
	               LAST);
	
	lr_xml_extract("XML={AnotherResult}",
	               "Query=/dwml/data/parameters/humidity[1]/value/text()",
	               "XMLFragmentParam=maxHumidity",
	               "NotFound=continue",
	               LAST);
	
	lr_xml_extract("XML={AnotherResult}",
	               "Query=/dwml/data/parameters/temperature[3]/value/text()",
	               "XMLFragmentParam=dewPoint",
	               "NotFound=continue",
	               LAST);
	
	lr_xml_extract("XML={AnotherResult}",
	               "Query=/dwml/data/parameters/wind-speed[1]/value/text()",
	               "XMLFragmentParam=windSpeed",
	               "NotFound=continue",
	               LAST);
}

// Вывод параметров в output
void printWetherParametrsToConsole(){
	lr_output_message(lr_eval_string("maxTemp: {maxTemp}"));
	lr_output_message(lr_eval_string("minTemp: {minTemp}"));
	lr_output_message(lr_eval_string("maxHumidity: {maxHumidity}"));
	lr_output_message(lr_eval_string("dewPoint: {dewPoint}"));
	lr_output_message(lr_eval_string("windSpeed: {windSpeed}"));
}

// Печать параметров в файл
void writeParametrsToFile(char * file){
	char* city = lr_eval_string("{city}\"");
	char* maxTemp = lr_eval_string("{maxTemp}");
	char* minTemp = lr_eval_string("{minTemp}");
	char* maxHumidity = lr_eval_string("{maxHumidity}");
	char* dewPoint = lr_eval_string("{dewPoint}");
	char* windSpeed = lr_eval_string("{windSpeed}");
	
	writeFile(file, city, maxTemp, minTemp, maxHumidity, dewPoint, windSpeed);
}


#endif