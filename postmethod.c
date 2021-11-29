#include"sensors.h"


esp_err_t devices_post_handler(httpd_req_t *req)
{
    char content[200];

    size_t recv_size = MIN(req->content_len, sizeof(content));

    int ret = httpd_req_recv(req, content, recv_size);
    if (ret <= 0) {
        if (ret == HTTPD_SOCK_ERR_TIMEOUT) {

            httpd_resp_send_408(req);
        }
        return ESP_FAIL;
    }

int sensorId,outputId;
        //oblik id-mjerenje#id-mjerenje
       // char sample[20]={"1-3#2-4#2-1#"};
        
        char* word_token=strtok(content,"#");
        while( word_token != NULL ) {
                printf("%s jedna word \n",word_token);
                sensorId=atoi(&word_token[0]);
		//1 plocica za garazu i kucu
		switch (sensorId){
			case 0:{
			       //servo
				ser.value=servo();
			       }
			case 1:{
			      // buzzer
			       
			       }
			 
			   case 2:{
				  //LED1
				  }
			   case 3:{
				  //LED2
				  
				  }
			   case 4:{
				  //LED3
				  }
		
		
		
		}
      
                word_token = strtok(NULL, "#");
                }

    const char resp[] = "URI POST Response";
    httpd_resp_send(req, resp, -1);
    return ESP_OK;
}



httpd_uri_t devicesPost = {
    .uri = "/devices",
    .method = HTTP_POST,
    .handler = devices_post_handler,
};




esp_err_t devices_client_get_handler(httpd_req_t *req)
{
   
 
    // }
	
    httpd_resp_send(req,sendBuffer, strlen(sendBuffer));

	//memset(sendBuffer,0,sizeof(sendBuffer)+1);

    return ESP_OK;
}

httpd_uri_t devicesGetClient = {
    .uri       = "/devices",
    .method    = HTTP_GET,
    .handler   = devices_client_get_handler,
};
