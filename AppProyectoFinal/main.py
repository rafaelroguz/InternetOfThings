import kivy
kivy.require('1.9.0')

from kivy.app import App
from kivy.uix.label import Label
from kivy.uix.gridlayout import GridLayout
from kivy.uix.textinput import TextInput
from kivy.uix.button import Button
from Adafruit_IO import Client


# ADAFRUIT_IO_KEY = '60255f7bc1a94c39905492e04d8d7c2b'
# ADAFRUIT_IO_USERNAME = 'victorox100'

ADAFRUIT_IO_KEY = '1cee6e836738402582666a4a98ed154c'
ADAFRUIT_IO_USERNAME = 'rafaelroguz'

aio = Client(ADAFRUIT_IO_USERNAME, ADAFRUIT_IO_KEY)


class MyGrid(GridLayout):

    def __init__(self, **kwargs):
        super(MyGrid, self).__init__(**kwargs)
        self.cols = 1

        self.inside = GridLayout()
        self.inside.cols = 2

        self.inside.add_widget(Label(text="Temperature:", font_size=30))
        self.temperatura = TextInput(multiline=False, font_size='30sp')
        self.inside.add_widget(self.temperatura)

        self.inside.add_widget(Label(text="Alarma:", font_size=30))
        self.alarmita = TextInput(multiline=False, font_size='30sp')
        self.inside.add_widget(self.alarmita)

        self.add_widget(self.inside)

        self.sendon = Button(text="LED On", font_size=40)
        self.sendon.bind(on_press=self.sendmqtt_on)
        self.add_widget(self.sendon)

        self.sendoff = Button(text="LED Off", font_size=40)
        self.sendoff.bind(on_press=self.sendmqtt_off)
        self.add_widget(self.sendoff)

        self.sendalarm = Button(text="Alarm Off", font_size=40)
        self.sendalarm.bind(on_press=self.sendmqtt_alarm_off)
        self.add_widget(self.sendalarm)

        self.sendtemp = Button(text="Temperature", font_size=40)
        self.sendtemp.bind(on_press=self.sendmqtt_temperature)
        self.add_widget(self.sendtemp)

        self.alarmbtn = Button(text="Update", font_size=40)
        self.alarmbtn.bind(on_press=self.receiveUpdate)
        self.add_widget(self.alarmbtn)

    def sendmqtt_on(self, instance):
        aio.send('request', "LIGHTS_ON")
        data = aio.receive('request')
        print('Received value: {0}'.format(data.value))

    def sendmqtt_off(self, instance):
        aio.send('request', "LIGHTS_OFF")
        data = aio.receive('request')
        print('Received value: {0}'.format(data.value))

    def sendmqtt_alarm_off(self, instance):
        aio.send('request', "ALARM_OFF")
        data = aio.receive('request')
        print('Received value: {0}'.format(data.value))
        self.receiveUpdate

    def sendmqtt_temperature(self, instance):
        aio.send('request', "TEMPERATURE")
        data = aio.receive('request')
        temp = aio.receive('temperature')
        print('Received value: {0}'.format(data.value))
        print('Temperature: {0}'.format(temp.value))
        self.temperatura.text = temp.value

    def receiveUpdate(self, instance):
        alarma = aio.receive('alarm')
        self.alarmita.text = alarma.value


class MyApp(App):
    def build(self):
        return MyGrid()


if __name__ == "__main__":
    MyApp().run()