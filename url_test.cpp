/*
 * *************************************************************************************************
 * taskManager
 * Copyright (C) 2021 Friendcom
 * 
 * @file         : url_test.cpp
 * @author       : ekko
 * @version      : V1.0
 * @date         : 2022-01-08
 * @brief        : 
 * @details      : 
 * @attention    : 
 * 
 * Change History : 
 * 
 * 
 * 
 * *************************************************************************************************
 */
#include <json/json.h>
#include <curl/curl.h>
#include <stdio.h>
#include <string>
#include <iostream>

static size_t cb(char *d, size_t n, size_t l, void *p)
{
  (void)d;
  (void)p;
  return n*l;
}
bool url_test(char* url,char* name)
{
    auto curl = curl_easy_init();
    if(curl)
    {
      curl_easy_setopt(curl, CURLOPT_URL, url);
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cb);
      auto res = curl_easy_perform(curl);
      if(CURLE_OK == res) {
        long ct;
        /* ask for the content-type */
        res = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &ct);
        if((CURLE_OK == res))
        {
          if(ct == 200)
            std::cout << name << "连接成功,";
          else
            goto end;
        }
        double time = 0;
        res = curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &time);
        if((CURLE_OK == res))
          printf("延迟时间%.3f秒\n", time);
            /* always cleanup */
        curl_easy_cleanup(curl);
        return true;
      }
    }
    /* always cleanup */
    end:curl_easy_cleanup(curl);
    std::cout << name << "连接失败" << std::endl;
    return false;
}
int main(int argc,char** argv)
{
  if(argc != 3)
  {
    printf("example : ./url_test \"https://www.google.com\" \"谷歌\"\n");
  }
  else
  {
    url_test(argv[1],argv[2]);
  }
  return 0;
}
