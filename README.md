# PlatformIO Setup
If you upgraded your ESP-01's flash chip to 32MBits you will need a custom board file for PlatformIO.

Move `esp01_4m.json` to `%userprofile%\.platformio\boards\`

Rename `platformio.ini.example` to `platformio.ini`

# 3D Printing
The case requires a print nozzle of 1.75mm due to it's size. For best results print slowly at 0.06mm layer height. The model was designed for a printer capable of printing with with 0.2mm of accuracy.

# Home Assistant Configuration
## Customization
```yaml
light.11cb27a45c71:
  friendly_name: Thermostat Display
```
Replace `11cb27a45c71` with your display's MAC address (case sensitive)

## Automation Script
```yaml
- id: '1536963450591'
  alias: Update Thermostat
  trigger:
  - platform: time
    seconds: /10
  condition: []
  action:
  - service: mqtt.publish
    data:
      payload_template: >-
        {
            "time": {{ now().strftime('%s') }},
            "mode" : "{{state_attr("climate.thermostat", "operation_mode")}}",
            "status": "{{ states('climate.thermostat') }}",
            "target_temp": {{ state_attr('climate.thermostat','temperature') }},
            "indoor_temp": {{ state_attr('climate.thermostat', 'current_temperature') }},
            "outdoor_temp": {{ states('sensor.dark_sky_apparent_temperature') }},
            "condition_icon": "{{ states('sensor.dark_sky_icon') }}"
        }
      qos: 2
      topic: 11cb27a45c71/command
```
Replace `climate.thermostat` with your thermostat entity id

Replace `11cb27a45c71` with your display's MAC address (case sensitive)
