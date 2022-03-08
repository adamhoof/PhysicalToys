package main

func main() {
	mqttHandler := MQTTHandler{}
	cryptoQuery := CryptoQuery{}

	mqttHandler.SetupClientOptions()
	mqttHandler.CreateClient()
	mqttHandler.ConnectClient()
	processor, topic := mqttHandler.MQTTHandler(&cryptoQuery)
	mqttHandler.SetSubscription(&processor, &topic)

	select {}
}
