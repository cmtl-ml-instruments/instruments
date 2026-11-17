{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 9,
			"minor" : 0,
			"revision" : 7,
			"architecture" : "x64",
			"modernui" : 1
		}
,
		"classnamespace" : "box",
		"rect" : [ 346.0, 112.0, 469.104804684378905, 234.612383799372765 ],
		"openrect" : [ 0.0, 0.0, 416.940137878948008, 235.765963710806318 ],
		"openinpresentation" : 1,
		"default_fontname" : "Avenir",
		"gridsize" : [ 15.0, 15.0 ],
		"boxes" : [ 			{
				"box" : 				{
					"id" : "obj-45",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 4,
					"outlettype" : [ "float", "float", "float", "float" ],
					"patching_rect" : [ 145.67902398109436, 134.567911982536316, 276.543231964111328, 25.0 ],
					"text" : "unpack f f f f"
				}

			}
, 			{
				"box" : 				{
					"comment" : "duration, density, bandwidth, pitch",
					"id" : "obj-44",
					"index" : 0,
					"maxclass" : "inlet",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 154.320999979972839, 96.296303987503052, 30.0, 30.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-37",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 490.123495936393738, 216.049399971961975, 229.0, 25.0 ],
					"text" : "dur: $1 density $2 bandwidth $3 pitch $4"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-31",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 490.123495936393738, 258.024711966514587, 73.0, 25.0 ],
					"text" : "prepend set"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-29",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 490.123495936393738, 290.123479962348938, 312.345703959465027, 23.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 6.333333522081375, 40.318181157112122, 400.666678607463837, 23.0 ],
					"text" : "dur: 3000 density 200 bandwidth 130 pitch 131"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-35",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 346.725589871406555, 472.271344125270844, 47.0, 25.0 ],
					"text" : "pack f f"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-34",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "bang", "bang", "float" ],
					"patching_rect" : [ 355.367565870285034, 398.197264134883881, 41.0, 25.0 ],
					"text" : "t b b f"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-33",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"patching_rect" : [ 396.108309864997864, 437.703440129756927, 30.0, 25.0 ],
					"text" : "+ 0."
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-32",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"patching_rect" : [ 336.849045872688293, 437.703440129756927, 29.5, 25.0 ],
					"text" : "- 0."
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-30",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"patching_rect" : [ 355.367565870285034, 363.629360139369965, 29.5, 25.0 ],
					"text" : "/ 2."
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-26",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 346.725589871406555, 506.83924812078476, 39.0, 25.0 ],
					"text" : "$1 $2"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-22",
					"maxclass" : "slider",
					"numinlets" : 1,
					"numoutlets" : 1,
					"orientation" : 2,
					"outlettype" : [ "" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 366.478677868843079, 200.666384160518646, 29.545454263687134, 117.045453429222107 ],
					"presentation" : 1,
					"presentation_rect" : [ 221.333339929580688, 94.000002801418304, 35.170586258172989, 140.157487750053406 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_initial" : [ 60.0 ],
							"parameter_initial_enable" : 1,
							"parameter_longname" : "slider",
							"parameter_modmode" : 3,
							"parameter_shortname" : "slider",
							"parameter_type" : 0
						}

					}
,
					"varname" : "slider"
				}

			}
, 			{
				"box" : 				{
					"floatoutput" : 1,
					"id" : "obj-18",
					"maxclass" : "slider",
					"numinlets" : 1,
					"numoutlets" : 1,
					"orientation" : 2,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 339.318181872367859, 199.431816160678864, 22.727272510528564, 121.59090793132782 ],
					"presentation" : 1,
					"presentation_rect" : [ 164.666671574115753, 92.666669428348541, 40.800000607967377, 141.53930452466011 ],
					"size" : 48.0
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-9",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 273.524496704339981, 237.36363410949707, 68.666668713092804, 23.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 150.66667115688324, 68.000002026557922, 68.666668713092804, 23.0 ],
					"text" : "Bandwidth"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-7",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 164.772725701332092, 689.772720694541931, 286.170210719108582, 23.0 ],
					"text" : "dur (ms), pitch (0-127), env-interp (0-1), pan(0-127)"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-3",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 38.63636326789856, 728.409083962440491, 108.0, 25.0 ],
					"text" : "s grain-parameters"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-58",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 395.845136791467667, 237.36363410949707, 80.000002384185791, 23.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 221.333339929580688, 68.000002026557922, 80.000002384185791, 23.0 ],
					"text" : "Center Freq"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-16",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 482.716087937355042, 493.827199935913086, 153.24675178527832, 23.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 258.000007688999176, 160.000004768371582, 150.0, 23.0 ],
					"text" : "Grain panning range"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-82",
					"listmode" : 1,
					"maxclass" : "rslider",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 482.716087937355042, 517.283991932868958, 153.24675178527832, 25.974025726318359 ],
					"presentation" : 1,
					"presentation_rect" : [ 258.000007688999176, 193.333339095115662, 149.999998927116394, 25.531914710998535 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_initial" : [ 40, 80 ],
							"parameter_initial_enable" : 1,
							"parameter_invisible" : 1,
							"parameter_longname" : "rslider[1]",
							"parameter_modmode" : 0,
							"parameter_shortname" : "rslider[1]",
							"parameter_type" : 3
						}

					}
,
					"varname" : "rslider[1]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-12",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 289.602213978767395, 558.954540133476257, 153.24675178527832, 23.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 258.000007688999176, 95.333336174488068, 150.0, 23.0 ],
					"text" : "Frequency Range"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-27",
					"listmode" : 1,
					"maxclass" : "rslider",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 289.602213978767395, 586.115036129951477, 153.24675178527832, 25.974025726318359 ],
					"presentation" : 1,
					"presentation_rect" : [ 258.000007688999176, 132.666670620441437, 149.999998927116394, 25.531914710998535 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_initial" : [ 40, 80 ],
							"parameter_initial_enable" : 1,
							"parameter_invisible" : 1,
							"parameter_longname" : "rslider",
							"parameter_modmode" : 0,
							"parameter_shortname" : "rslider",
							"parameter_type" : 3
						}

					}
,
					"varname" : "rslider"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"id" : "obj-83",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 419.753119945526123, 49.999999523162842, 153.519675016403198, 27.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 0.666666686534882, 11.318181157112122, 412.000012278556824, 27.0 ],
					"text" : "CLOUD PARAMETERS"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-6",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 196.590907216072083, 412.703440129756927, 129.545453310012817, 23.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 7.333333551883698, 121.33333694934845, 127.737225592136383, 23.0 ],
					"text" : "Grain Density (grain/s)"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-52",
					"maxclass" : "number",
					"maximum" : 44100,
					"minimum" : 1,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 214.772725224494934, 442.045450329780579, 53.246752738952637, 25.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 7.333333551883698, 146.000004351139069, 53.246752738952637, 25.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_initial" : [ 1.0 ],
							"parameter_initial_enable" : 1,
							"parameter_longname" : "number",
							"parameter_mmax" : 44100.0,
							"parameter_mmin" : 1.0,
							"parameter_modmode" : 3,
							"parameter_shortname" : "number",
							"parameter_type" : 0
						}

					}
,
					"varname" : "number"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-46",
					"maxclass" : "number",
					"minimum" : 0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 62.499999403953552, 620.45453953742981, 53.246752738952637, 25.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 7.333333551883698, 94.000002801418304, 53.246752738952637, 25.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_initial" : [ 500 ],
							"parameter_initial_enable" : 1,
							"parameter_invisible" : 1,
							"parameter_longname" : "number[1]",
							"parameter_modmode" : 0,
							"parameter_shortname" : "number[1]",
							"parameter_type" : 3
						}

					}
,
					"varname" : "number[1]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-47",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 62.499999403953552, 587.602048993110657, 95.454544544219971, 23.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 7.333333551883698, 69.333335399627686, 102.27272629737854, 23.0 ],
					"text" : "Grain Dur (ms)"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-110",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 63.63636302947998, 265.909088373184204, 32.0, 25.0 ],
					"text" : "0"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-108",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 32.954545140266418, 265.909088373184204, 32.0, 25.0 ],
					"text" : "1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-106",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "bang", "bang" ],
					"patching_rect" : [ 39.772726893424988, 236.36363410949707, 44.0, 25.0 ],
					"text" : "edge~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-98",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"patching_rect" : [ 347.727269411087036, 620.45453953742981, 49.0, 25.0 ],
					"text" : "choose"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-91",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "bang", "bang" ],
					"patching_rect" : [ 196.590907216072083, 557.954540133476257, 34.0, 25.0 ],
					"text" : "t b b"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-81",
					"maxclass" : "toggle",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 43.181817770004272, 298.863633513450623, 26.0, 26.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Avenir",
					"id" : "obj-77",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 39.772726893424988, 155.681816697120667, 91.0, 39.0 ],
					"text" : "On/Off\nTurn into ADSR"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-62",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"patching_rect" : [ 232.954543232917786, 620.45453953742981, 78.0, 25.0 ],
					"text" : "choose"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-20",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"patching_rect" : [ 218.181816101074219, 487.499995350837708, 47.0, 25.0 ],
					"text" : "!/ 1000"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-19",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 196.590907216072083, 519.318176865577698, 41.0, 25.0 ],
					"text" : "metro"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-15",
					"maxclass" : "newobj",
					"numinlets" : 5,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 38.63636326789856, 688.636357069015503, 115.0, 25.0 ],
					"text" : "pack note 0. 0. 0. 0."
				}

			}
, 			{
				"box" : 				{
					"comment" : "On/Off Signal from ADSR",
					"id" : "obj-5",
					"index" : 0,
					"maxclass" : "inlet",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 39.772726893424988, 195.454543590545654, 32.0, 32.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-4",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 17.045454382896423, 49.999999523162842, 345.0, 39.0 ],
					"text" : "Input: List of parameters speciying cloud behavior\nOut: Stream of grain parameters (lists)"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 1,
					"fontsize" : 15.741614906832297,
					"id" : "obj-2",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 17.045454382896423, 13.636363506317139, 337.0, 28.0 ],
					"text" : "Higher-Level Organization - Cloud"
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-108", 0 ],
					"source" : [ "obj-106", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-110", 0 ],
					"source" : [ "obj-106", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-81", 0 ],
					"source" : [ "obj-108", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-81", 0 ],
					"source" : [ "obj-110", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-3", 0 ],
					"source" : [ "obj-15", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-30", 0 ],
					"midpoints" : [ 348.818181872367859, 345.257295191287994, 364.867565870285034, 345.257295191287994 ],
					"source" : [ "obj-18", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-91", 0 ],
					"source" : [ "obj-19", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-19", 1 ],
					"source" : [ "obj-20", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-32", 0 ],
					"midpoints" : [ 375.978677868843079, 348.257295191287994, 340.887773513793945, 348.257295191287994, 340.887773513793945, 432.257295191287994, 346.349045872688293, 432.257295191287994 ],
					"order" : 1,
					"source" : [ "obj-22", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 0 ],
					"midpoints" : [ 375.978677868843079, 348.257295191287994, 406.887773513793945, 348.257295191287994, 406.887773513793945, 432.257295191287994, 405.608309864997864, 432.257295191287994 ],
					"order" : 0,
					"source" : [ "obj-22", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-27", 0 ],
					"midpoints" : [ 356.225589871406555, 543.0, 276.0, 543.0, 276.0, 582.0, 299.102213978767395, 582.0 ],
					"source" : [ "obj-26", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-62", 1 ],
					"source" : [ "obj-27", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-34", 0 ],
					"source" : [ "obj-30", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-29", 0 ],
					"source" : [ "obj-31", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-35", 0 ],
					"source" : [ "obj-32", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-35", 1 ],
					"source" : [ "obj-33", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-32", 1 ],
					"order" : 1,
					"source" : [ "obj-34", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-32", 0 ],
					"source" : [ "obj-34", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 1 ],
					"order" : 0,
					"source" : [ "obj-34", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 0 ],
					"source" : [ "obj-34", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-26", 0 ],
					"source" : [ "obj-35", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-31", 0 ],
					"source" : [ "obj-37", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-37", 0 ],
					"midpoints" : [ 163.820999979972839, 129.0, 141.0, 129.0, 141.0, 186.0, 499.623495936393738, 186.0 ],
					"order" : 0,
					"source" : [ "obj-44", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-45", 0 ],
					"order" : 1,
					"source" : [ "obj-44", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-18", 0 ],
					"source" : [ "obj-45", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-22", 0 ],
					"source" : [ "obj-45", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-46", 0 ],
					"source" : [ "obj-45", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-52", 0 ],
					"source" : [ "obj-45", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-15", 1 ],
					"source" : [ "obj-46", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-106", 0 ],
					"source" : [ "obj-5", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-20", 0 ],
					"source" : [ "obj-52", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-15", 2 ],
					"midpoints" : [ 242.454543232917786, 666.435086369514465, 96.13636326789856, 666.435086369514465 ],
					"source" : [ "obj-62", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-19", 0 ],
					"midpoints" : [ 52.681817770004272, 503.86363685131073, 206.090907216072083, 503.86363685131073 ],
					"source" : [ "obj-81", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-98", 1 ],
					"midpoints" : [ 492.216087937355042, 621.0, 396.0, 621.0, 396.0, 615.0, 387.227269411087036, 615.0 ],
					"source" : [ "obj-82", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-15", 0 ],
					"midpoints" : [ 206.090907216072083, 674.86363685131073, 48.13636326789856, 674.86363685131073 ],
					"source" : [ "obj-91", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-62", 0 ],
					"midpoints" : [ 221.090907216072083, 605.86363685131073, 242.454543232917786, 605.86363685131073 ],
					"order" : 1,
					"source" : [ "obj-91", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-98", 0 ],
					"midpoints" : [ 221.090907216072083, 605.86363685131073, 357.227269411087036, 605.86363685131073 ],
					"order" : 0,
					"source" : [ "obj-91", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-15", 4 ],
					"midpoints" : [ 357.227269411087036, 674.86363685131073, 144.13636326789856, 674.86363685131073 ],
					"source" : [ "obj-98", 0 ]
				}

			}
 ],
		"parameters" : 		{
			"obj-22" : [ "slider", "slider", 0 ],
			"obj-27" : [ "rslider", "rslider", 0 ],
			"obj-46" : [ "number[1]", "number[1]", 0 ],
			"obj-52" : [ "number", "number", 0 ],
			"obj-82" : [ "rslider[1]", "rslider[1]", 0 ],
			"parameterbanks" : 			{
				"0" : 				{
					"index" : 0,
					"name" : "",
					"parameters" : [ "-", "-", "-", "-", "-", "-", "-", "-" ]
				}

			}
,
			"inherited_shortname" : 1
		}
,
		"dependency_cache" : [ 			{
				"name" : "choose.maxpat",
				"bootpath" : "~/git/instruments/group-1/granular-synth/patchers",
				"patcherrelativepath" : ".",
				"type" : "JSON",
				"implicit" : 1
			}
 ],
		"autosave" : 0,
		"boxgroups" : [ 			{
				"boxes" : [ "obj-82", "obj-16" ]
			}
, 			{
				"boxes" : [ "obj-27", "obj-12" ]
			}
 ]
	}

}
