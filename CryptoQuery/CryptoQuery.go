package main

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
)

type CryptoQuery struct {
}

func (cryptoQuery *CryptoQuery) RequestData(cryptoCurrency string) *http.Response {
	request := "https://api.coingecko.com/api/v3/coins/markets?vs_currency=usd&ids=" + cryptoCurrency + "&order=market_cap_desc&per_page=1&page=1&price_change_percentage=24h%2C7d%2C14d%2C30d"
	response, err := http.Get(request)
	if err != nil {
		log.Fatalln("failed to get response", err)
	}
	return response
}

func (cryptoQuery *CryptoQuery) CreateBody(response *http.Response) []byte {
	body, err := ioutil.ReadAll(response.Body)
	if err != nil {
		log.Fatalln(err)
	}
	return body
}

func (cryptoQuery *CryptoQuery) FilterUnwanted(body []byte) []byte {
	var queryResultMap []map[string]interface{}
	err := json.Unmarshal(body, &queryResultMap)
	if err != nil {
		fmt.Println(err)
	}

	filteredData := make(map[string]interface{})
	filteredData["price"] = queryResultMap[0]["current_price"]
	filteredData["high_24h"] = queryResultMap[0]["high_24h"]
	filteredData["low_24h"] = queryResultMap[0]["low_24h"]
	filteredData["price_change_24h"] = queryResultMap[0]["price_change_24h"]
	filteredData["pc_change_perc_24h"] = queryResultMap[0]["price_change_percentage_24h"]
	filteredData["pc_change_perc_7d"] = queryResultMap[0]["price_change_percentage_7d_in_currency"]
	filteredData["pc_change_perc_14d"] = queryResultMap[0]["price_change_percentage_14d_in_currency"]

	filteredDataJson, err := json.Marshal(filteredData)
	return filteredDataJson
}
