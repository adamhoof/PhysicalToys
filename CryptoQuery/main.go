package main

func main() {
	mqttHandler := MQTTHandler{}

	mqttHandler.SetupClientOptions()
	mqttHandler.CreateClient()
	mqttHandler.ConnectClient()

	select {

	}
}
