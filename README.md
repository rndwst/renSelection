# renSelection 
![](https://github.com/rndwst/renSelection/blob/main/screenshot/Screenshot%20(21).png)

#### Function
```
ren_ShowPlayerSelection(playerid, selectionid, header[], button1[], button2[], Float:rotx = -10.000000, Float:roty = 0.000000, Float:rotz = -20.000000, Float:zoom = 1.000000)
ren_AddSelectionModel(playerid, modelid, description[] = "Description", carcolor1 = 1, carcolor2 = 1)
ren_SelectionSetColor(boxcolor = 125, modelcolor = -131, buttoncolor = -131)
```

#### Callback
```
OnSelectionResponse(playerid, response, selectionid, modelid)
```

### Kegunaan
Berguna untuk menampilkan selection
```ren_ShowPlayerSelection```

Berguna untuk menambahkan model
```ren_AddSelectionModel```

Berguna untuk mengubah warna selection ( taruh di OnGameModeInit )
```ren_SelectionSetColor```

Nama warna perbagian 
![](https://github.com/rndwst/renSelection/blob/main/screenshot/Screenshot%20(22).png)
