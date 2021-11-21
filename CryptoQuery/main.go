package main

func main() {
	mqttHandler := MQTTHandler{}
	cryptoQuery := CryptoQuery{}

	mqttHandler.SetupClientOptions()
	mqttHandler.CreateClient()
	mqttHandler.ConnectClient()
	processor, topic := mqttHandler.MQTTProcessor(&cryptoQuery)
	mqttHandler.SetSubscription(&processor, &topic)

	select {

	}
}
