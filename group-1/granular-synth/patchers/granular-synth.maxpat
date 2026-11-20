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
		"rect" : [ -64.0, 108.0, 796.0, 605.0 ],
		"openinpresentation" : 1,
		"default_fontname" : "Avenir",
		"gridsize" : [ 15.0, 15.0 ],
		"boxes" : [ 			{
				"box" : 				{
					"id" : "obj-60",
					"linecount" : 10,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 993.327610969543457, 376.390252590179443, 150.0, 170.0 ],
					"presentation" : 1,
					"presentation_linecount" : 10,
					"presentation_rect" : [ 791.269853532314301, 389.5, 150.0, 170.0 ],
					"text" : "dur 3000 grain density 6, freq range low up to a little more than half\nmenacingly beautiful\n- 20 316 42 91. horror\n\non low frequencies below normal. it seems to delay the past history!!! It's so crazy!"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-23",
					"linecount" : 3,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 997.0, 450.390252590179443, 150.0, 56.0 ],
					"presentation" : 1,
					"presentation_linecount" : 3,
					"presentation_rect" : [ 800.0, 576.0, 150.0, 56.0 ],
					"text" : "dur 3000, density 1, bandwidth 36, pitch 60\nhow nice!"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-74",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 24.193548560142517, 916.12903881072998, 35.0, 25.0 ],
					"text" : "reset"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-70",
					"maxclass" : "newobj",
					"numinlets" : 3,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 93.254735946655273, 946.774200320243835, 59.0, 25.0 ],
					"text" : "clip~ -1 1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-69",
					"maxclass" : "newobj",
					"numinlets" : 3,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 122.306683540344238, 973.774200320243835, 59.0, 25.0 ],
					"text" : "clip~ -1 1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-68",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 1044.444494247436523, 573.623371124267578, 73.533098340034485, 39.0 ],
					"presentation" : 1,
					"presentation_linecount" : 2,
					"presentation_rect" : [ 629.268292307853699, 159.222221374511719, 73.533098340034485, 39.0 ],
					"text" : "vibrato duty-cycle"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-52",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 1146.666700839996338, 644.0, 90.0, 39.0 ],
					"text" : "could also edit >reinitialize"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-42",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 1051.444494247436523, 648.623371124267578, 34.0, 25.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 635.438702583312988, 234.988456726074219, 34.0, 25.0 ],
					"text" : "0.66"
				}

			}
, 			{
				"box" : 				{
					"floatoutput" : 1,
					"id" : "obj-12",
					"maxclass" : "dial",
					"mult" : 0.01,
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 1051.444494247436523, 611.623371124267578, 33.766233444213867, 33.766233444213867 ],
					"presentation" : 1,
					"presentation_rect" : [ 635.555585861206055, 199.222223281860352, 33.766233444213867, 33.766233444213867 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_initial" : [ 66.0 ],
							"parameter_initial_enable" : 1,
							"parameter_longname" : "dial[4]",
							"parameter_mmax" : 100.0,
							"parameter_modmode" : 3,
							"parameter_shortname" : "dial",
							"parameter_type" : 0
						}

					}
,
					"size" : 100.0,
					"varname" : "dial[4]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-7",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 9,
							"minor" : 0,
							"revision" : 7,
							"architecture" : "x64",
							"modernui" : 1
						}
,
						"classnamespace" : "box",
						"rect" : [ 209.0, 135.0, 254.0, 334.0 ],
						"gridsize" : [ 15.0, 15.0 ],
						"visible" : 1,
						"boxes" : [ 							{
								"box" : 								{
									"id" : "obj-8",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 83.0, 42.0, 150.0, 20.0 ],
									"text" : "Bang to reinitialize"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-6",
									"maxclass" : "button",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 43.0, 81.0, 24.0, 24.0 ]
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"id" : "obj-4",
									"index" : 1,
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"patching_rect" : [ 43.0, 37.0, 30.0, 30.0 ]
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-15",
									"linecount" : 4,
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 43.0, 128.0, 102.0, 62.0 ],
									"text" : ";\rduty-cycle 0.66;\rdamp-switch 1;\rdamp-time 10000"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-6", 0 ],
									"source" : [ "obj-4", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-15", 0 ],
									"source" : [ "obj-6", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 1156.0, 621.543988108634949, 50.0, 25.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 723.577235341072083, 212.040650546550751, 50.0, 25.0 ],
					"text" : "p re-init"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-8",
					"maxclass" : "button",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 1156.0, 589.543988108634949, 24.0, 24.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 723.577235341072083, 180.333333492279053, 24.0, 24.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-4",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 935.0, 675.623371124267578, 76.0, 25.0 ],
					"text" : "s damp-time"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-5",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 884.0, 643.623371124267578, 85.0, 25.0 ],
					"text" : "s damp-switch"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-127",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 935.0, 581.623371124267578, 79.333335697650909, 23.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 518.888913631439209, 177.0, 79.333335697650909, 23.0 ],
					"text" : "damp time"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-125",
					"maxclass" : "number",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 935.0, 608.623371124267578, 50.0, 25.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 518.888913631439209, 203.666667938232422, 50.0, 25.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_initial" : [ 10000 ],
							"parameter_initial_enable" : 1,
							"parameter_invisible" : 1,
							"parameter_longname" : "number[6]",
							"parameter_modmode" : 0,
							"parameter_shortname" : "number",
							"parameter_type" : 3
						}

					}
,
					"varname" : "number"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-122",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 880.0, 581.623371124267578, 44.666667997837067, 23.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 464.444466590881348, 177.0, 44.666667997837067, 23.0 ],
					"text" : "on/off"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-81",
					"maxclass" : "toggle",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 884.0, 609.623371124267578, 24.0, 24.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 468.888911247253418, 204.777779102325439, 24.0, 24.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_enum" : [ "off", "on" ],
							"parameter_initial" : [ 1.0 ],
							"parameter_initial_enable" : 1,
							"parameter_longname" : "toggle",
							"parameter_mmax" : 1,
							"parameter_modmode" : 0,
							"parameter_shortname" : "toggle",
							"parameter_type" : 2
						}

					}
,
					"varname" : "toggle"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-76",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 880.0, 563.623371124267578, 150.0, 23.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 464.444466590881348, 159.222221374511719, 150.0, 23.0 ],
					"text" : "damped sustain"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-1",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 1051.444494247436523, 678.623371124267578, 72.0, 25.0 ],
					"text" : "s duty-cycle"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-171",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 612.012980461120605, 303.757300786410724, 75.0, 23.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 53.0, 240.0, 73.0, 23.0 ],
					"text" : "It's working!"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-169",
					"linecount" : 4,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 800.000039100646973, 383.333329677581787, 150.0, 72.0 ],
					"presentation" : 1,
					"presentation_linecount" : 4,
					"presentation_rect" : [ 443.0, 502.0, 150.0, 72.0 ],
					"text" : "POSES\n1. Simple sustained note\n2. Sustained formant\n3. Sparse Noise"
				}

			}
, 			{
				"box" : 				{
					"bgmode" : 0,
					"border" : 0,
					"clickthrough" : 0,
					"enablehscroll" : 0,
					"enablevscroll" : 0,
					"id" : "obj-167",
					"lockeddragscroll" : 0,
					"lockedsize" : 0,
					"maxclass" : "bpatcher",
					"name" : "cloud.maxpat",
					"numinlets" : 2,
					"numoutlets" : 0,
					"offset" : [ 0.0, 0.0 ],
					"patching_rect" : [ 73.067701935768127, 399.21875, 416.940137878948008, 235.765963710806318 ],
					"presentation" : 1,
					"presentation_rect" : [ 18.0, 366.0, 416.940137878948008, 235.765963710806318 ],
					"viewvisibility" : 1
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-92",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 427.30602240562439, 656.043988108634949, 85.0, 25.0 ],
					"text" : "r cloud-toggle"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-87",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 340.659357309341431, 185.126509666442871, 52.747255325317383, 23.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 299.0, 177.0, 52.747255325317383, 23.0 ],
					"text" : "START"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-84",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 316.703311204910278, 255.601133108139038, 86.0, 25.0 ],
					"text" : "s cloud-toggle"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-83",
					"int" : 1,
					"maxclass" : "gswitch2",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 296.703311204910278, 219.192445397377014, 39.0, 32.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-79",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "int", "int" ],
					"patching_rect" : [ 316.483531951904297, 84.027603626251221, 29.5, 25.0 ],
					"text" : "t i i"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-77",
					"maxclass" : "toggle",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 316.483531951904297, 184.027608513832092, 24.0, 24.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 219.0, 161.0, 74.613134023780844, 74.613134023780844 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-75",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 316.483531951904297, 152.159475088119507, 29.5, 25.0 ],
					"text" : "0"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-73",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "int", "int" ],
					"patching_rect" : [ 316.483531951904297, 121.3902428150177, 48.0, 25.0 ],
					"text" : "change"
				}

			}
, 			{
				"box" : 				{
					"bgmode" : 0,
					"border" : 0,
					"clickthrough" : 0,
					"enablehscroll" : 0,
					"enablevscroll" : 0,
					"id" : "obj-72",
					"lockeddragscroll" : 0,
					"lockedsize" : 0,
					"maxclass" : "bpatcher",
					"name" : "single-grain-parameters.maxpat",
					"numinlets" : 1,
					"numoutlets" : 0,
					"offset" : [ 0.0, 0.0 ],
					"patching_rect" : [ 67.93151759687953, 300.000014662742615, 496.543587216061496, 81.514572247336218 ],
					"presentation" : 1,
					"presentation_rect" : [ 18.0, 272.0, 496.543587216061496, 81.514572247336218 ],
					"viewvisibility" : 1
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-66",
					"maxclass" : "button",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 670.329703092575073, 328.757300786410724, 24.0, 24.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 27.0, 240.0, 24.0, 24.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontface" : 0,
					"fontname" : "Avenir",
					"fontsize" : 12.0,
					"id" : "obj-15",
					"maxclass" : "number~",
					"mode" : 2,
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "signal", "float" ],
					"patching_rect" : [ 503.0, 876.0, 56.0, 25.0 ],
					"sig" : 0.0
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-67",
					"linecount" : 15,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 516.0, 21.522109389305115, 151.0, 252.0 ],
					"text" : "TODO: Implement button holding logic, then use that to get all states in iris\nTODO: implement violin as grain generator\nTODO: Use gen~ in violin to get higher frequencies.\nTODO: Parameterize violin grain to include pitch vibrato depth, and when it occurs.\nTODO: Implement retrigger  method for the envelope (hard b/c it is reading from buffer)"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-61",
					"linecount" : 7,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 800.000039100646973, 253.390252590179443, 317.977553486824036, 121.0 ],
					"presentation" : 1,
					"presentation_linecount" : 7,
					"presentation_rect" : [ 443.0, 373.0, 317.977553486824036, 121.0 ],
					"text" : "MAPPING\n1. handle linear acceleration -> duration: ms, 2-3000 \n2. end angular velocity -> density: grain/s, 0-200\n3. end angular accel -> bandwidth: midi 0-80\n4. handle linear height -> pitch: midi, 12-108 (C0-C8)\n1-3 can be exponential, 4 linear. In between states will help solidify that."
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-51",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 701.09893536567688, 21.522109389305115, 245.177890181541443, 23.0 ],
					"text" : "SERIAL INPUT FROM ESP-32"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-13",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "int", "int" ],
					"patching_rect" : [ 701.09893536567688, 152.291346549987793, 29.5, 25.0 ],
					"text" : "t i i"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-21",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 796.703335642814636, 69.873760104179382, 150.0, 39.0 ],
					"presentation" : 1,
					"presentation_linecount" : 4,
					"presentation_rect" : [ 107.0, 162.0, 92.30769681930542, 72.0 ],
					"text" : "Turn serial on (turn off if flashing new code)"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-22",
					"linecount" : 5,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 978.02202582359314, 140.203433871269226, 155.0, 88.0 ],
					"text" : "Press print, to see a list of available ports in console. Change the letter to the one corresponding to your port."
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-27",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 701.09893536567688, 263.280362963676453, 78.0, 25.0 ],
					"text" : "serial-to-max"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-34",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 927.472572803497314, 179.763875365257263, 41.0, 25.0 ],
					"text" : "open"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-35",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 871.428614020347595, 179.763875365257263, 37.0, 25.0 ],
					"text" : "close"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-37",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "int", "" ],
					"patching_rect" : [ 701.09893536567688, 224.818822622299194, 90.0, 25.0 ],
					"text" : "serial b 115200"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-64",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "bang", "" ],
					"patching_rect" : [ 885.71432900428772, 140.203433871269226, 34.0, 25.0 ],
					"text" : "sel 0"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-38",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 796.703335642814636, 179.763875365257263, 39.0, 25.0 ],
					"text" : "print"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-57",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 700.000034213066101, 187.456183433532715, 63.0, 25.0 ],
					"text" : "metro 10"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-46",
					"maxclass" : "toggle",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 701.09893536567688, 53.3902428150177, 93.0, 93.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 27.0, 161.0, 75.803610202903769, 75.803610202903769 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-9",
					"linecount" : 5,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 1178.022035598754883, 763.736301064491272, 91.0, 88.0 ],
					"text" : "Either double click bpatcher or open its file to view contents"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-17",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"patching_rect" : [ 123.076929092407227, 227.472538590431213, 46.0, 25.0 ],
					"text" : "!/ 1000"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-16",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 4,
					"outlettype" : [ "signal", "signal", "float", "float" ],
					"patching_rect" : [ 24.193548560142517, 946.774200320243835, 59.0, 25.0 ],
					"text" : "minmax~"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 0,
					"fontname" : "Avenir",
					"fontsize" : 12.0,
					"id" : "obj-2",
					"maxclass" : "number~",
					"mode" : 2,
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "signal", "float" ],
					"patching_rect" : [ 25.806451797485352, 975.806458592414856, 56.0, 25.0 ],
					"sig" : 0.0
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-49",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 892.0, 986.77921199798584, 50.0, 25.0 ],
					"text" : "0.272"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-31",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 922.0, 950.77921199798584, 113.0, 25.0 ],
					"text" : "expr $f1/1000 * $f2"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-19",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 919.0, 920.77921199798584, 29.5, 25.0 ],
					"text" : "pak"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-14",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 866.0, 1013.77921199798584, 102.0, 23.0 ],
					"text" : "Fill Factor (FF)"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 1,
					"fontname" : "Avenir",
					"fontsize" : 22.547671219335388,
					"id" : "obj-6",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 36.046510338783264, 9.302325248718262, 243.0, 37.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 8.0, 5.0, 243.0, 37.0 ],
					"text" : "Granular Synth",
					"underline" : 1
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-3",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 92.168827056884766, 662.921401262283325, 107.0, 25.0 ],
					"text" : "r grain-parameters"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-28",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 20.879121899604797, 205.494515538215637, 95.0, 39.0 ],
					"presentation" : 1,
					"presentation_linecount" : 3,
					"presentation_rect" : [ 523.0, 272.0, 88.0, 56.0 ],
					"text" : "Single-Grain Density (grain/s)"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 0,
					"fontname" : "Avenir",
					"fontsize" : 12.0,
					"id" : "obj-43",
					"maxclass" : "number~",
					"mode" : 2,
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "signal", "float" ],
					"patching_rect" : [ 325.876710891723633, 859.550630450248718, 56.0, 25.0 ],
					"sig" : 0.0
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-11",
					"maxclass" : "button",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 73.067701935768127, 737.078710556030273, 24.0, 24.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-29",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 113.517143368721008, 712.359607458114624, 184.415582656860352, 23.0 ],
					"text" : "Per-grain parameter message"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-24",
					"linecount" : 3,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 622.0, 737.078710556030273, 153.24675178527832, 56.0 ],
					"text" : "On single grain, pass signal. on cloud, use adsr of notein for cloud."
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-88",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 910.989055514335632, 739.560475707054138, 260.227270245552063, 23.0 ],
					"text" : "Grain Envelopes (Bpatcher)"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-50",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 334.065950393676758, 35.164836883544922, 103.896102905273438, 39.0 ],
					"presentation" : 1,
					"presentation_linecount" : 2,
					"presentation_rect" : [ 50.0, 46.0, 101.149423599243164, 39.0 ],
					"text" : "Single Grain\nGranular Synth"
				}

			}
, 			{
				"box" : 				{
					"disabled" : [ 0, 0 ],
					"id" : "obj-45",
					"itemtype" : 0,
					"maxclass" : "radiogroup",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 312.087927341461182, 35.164836883544922, 136.363635063171387, 34.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 27.0, 46.0, 134.0000039935112, 34.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_enum" : [ "0", "1" ],
							"parameter_initial" : [ 1 ],
							"parameter_initial_enable" : 1,
							"parameter_longname" : "radiogroup",
							"parameter_mmax" : 1,
							"parameter_modmode" : 0,
							"parameter_shortname" : "radiogroup",
							"parameter_type" : 2
						}

					}
,
					"size" : 2,
					"value" : 1,
					"varname" : "radiogroup"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-44",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 360.689326763153076, 84.027603626251221, 50.649350166320801, 25.0 ],
					"text" : "s mode"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-41",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"patching_rect" : [ 463.0, 781.0, 32.467532157897949, 25.0 ],
					"text" : "+ 1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-40",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 464.0, 720.0, 49.350648880004883, 25.0 ],
					"text" : "r mode"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-39",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 499.0, 781.0, 44.155843734741211, 25.0 ],
					"text" : "sig~ 1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-36",
					"maxclass" : "newobj",
					"numinlets" : 3,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 474.0, 809.0, 150.0, 25.0 ],
					"text" : "selector~ 2 @ramptime 20"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-33",
					"maxclass" : "number",
					"minimum" : 1,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 120.879126787185669, 194.505504012107849, 53.246752738952637, 25.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 523.0, 332.0, 50.0, 25.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_initial" : [ 1 ],
							"parameter_initial_enable" : 1,
							"parameter_invisible" : 1,
							"parameter_longname" : "number[3]",
							"parameter_mmin" : 1.0,
							"parameter_modmode" : 0,
							"parameter_shortname" : "number[3]",
							"parameter_type" : 3
						}

					}
,
					"varname" : "number[3]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-202",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 194.41602623462677, 850.5618656873703, 32.467532157897949, 25.0 ],
					"text" : "*~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-200",
					"maxclass" : "number",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 751.550490736961365, 629.213533401489258, 53.246752738952637, 25.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-197",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "int", "int", "int" ],
					"patching_rect" : [ 807.730270504951477, 593.258474349975586, 44.155843734741211, 25.0 ],
					"text" : "notein"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-136",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"patching_rect" : [ 820.089822053909302, 629.213533401489258, 41.558441162109375, 25.0 ],
					"text" : "/ 127."
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-99",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 88.798040270805359, 850.5618656873703, 32.467532157897949, 25.0 ],
					"text" : "*~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-48",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 703.24674654006958, 646.155838012695312, 42.857142448425293, 25.0 ],
					"text" : "500"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-32",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 651.94804573059082, 641.558435440063477, 37.662337303161621, 25.0 ],
					"text" : "0.5"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-30",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 597.402591705322266, 641.558435440063477, 42.857142448425293, 25.0 ],
					"text" : "50"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-26",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 544.155838966369629, 641.558435440063477, 38.961038589477539, 25.0 ],
					"text" : "20"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-105",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 540.259735107421875, 553.246747970581055, 214.285712242126465, 23.0 ],
					"text" : "Cloud ADSR (not useful yet)"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-53",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 540.259735107421875, 576.623371124267578, 49.350648880004883, 36.0 ],
					"style" : "helpfile_label",
					"text" : "attack time",
					"textjustification" : 1
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-89",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 593.506487846374512, 576.623371124267578, 50.649350166320801, 36.0 ],
					"style" : "helpfile_label",
					"text" : "decay time",
					"textjustification" : 1
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-55",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 644.155838012695312, 576.623371124267578, 55.844155311584473, 36.0 ],
					"style" : "helpfile_label",
					"text" : "sustain gain ",
					"textjustification" : 1
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-56",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 697.402590751647949, 576.623371124267578, 58.441557884216309, 36.0 ],
					"style" : "helpfile_label",
					"text" : "release time",
					"textjustification" : 1
				}

			}
, 			{
				"box" : 				{
					"floatoutput" : 1,
					"id" : "obj-90",
					"maxclass" : "dial",
					"mult" : 0.01,
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 653.246747016906738, 610.389604568481445, 33.766233444213867, 33.766233444213867 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_initial" : [ 50 ],
							"parameter_initial_enable" : 1,
							"parameter_longname" : "dial[1]",
							"parameter_mmax" : 100.0,
							"parameter_modmode" : 3,
							"parameter_shortname" : "dial[1]",
							"parameter_type" : 0
						}

					}
,
					"size" : 100.0,
					"varname" : "dial[1]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-91",
					"maxclass" : "dial",
					"mult" : 10.0,
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 707.792201042175293, 610.389604568481445, 33.766233444213867, 33.766233444213867 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_initial" : [ 50 ],
							"parameter_initial_enable" : 1,
							"parameter_longname" : "dial",
							"parameter_mmax" : 99.0,
							"parameter_modmode" : 3,
							"parameter_shortname" : "dial",
							"parameter_type" : 0
						}

					}
,
					"size" : 100.0,
					"varname" : "dial"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-59",
					"maxclass" : "dial",
					"mult" : 10.0,
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 601.29869556427002, 610.389604568481445, 33.766233444213867, 33.766233444213867 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_initial" : [ 5 ],
							"parameter_initial_enable" : 1,
							"parameter_longname" : "dial[2]",
							"parameter_mmax" : 99.0,
							"parameter_modmode" : 3,
							"parameter_shortname" : "dial[2]",
							"parameter_type" : 0
						}

					}
,
					"size" : 100.0,
					"varname" : "dial[2]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-25",
					"maxclass" : "dial",
					"mult" : 10.0,
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 545.454540252685547, 610.389604568481445, 33.766233444213867, 33.766233444213867 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_initial" : [ 2 ],
							"parameter_initial_enable" : 1,
							"parameter_longname" : "dial[3]",
							"parameter_mmax" : 99.0,
							"parameter_modmode" : 3,
							"parameter_shortname" : "dial[3]",
							"parameter_type" : 0
						}

					}
,
					"size" : 100.0,
					"varname" : "dial[3]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-85",
					"maxclass" : "newobj",
					"numinlets" : 5,
					"numoutlets" : 4,
					"outlettype" : [ "signal", "signal", "", "" ],
					"patching_rect" : [ 553.966616749763489, 706.741629481315613, 63.63636302947998, 25.0 ],
					"text" : "adsr~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-78",
					"logfreq" : 1,
					"maxclass" : "spectroscope~",
					"monochrome" : 0,
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 448.387099981307983, 958.870974600315094, 240.0, 65.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 410.0, 46.0, 237.0, 64.0 ],
					"scroll" : 2,
					"sono" : 1
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-10",
					"logfreq" : 1,
					"maxclass" : "spectroscope~",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 194.354840099811554, 958.870974600315094, 240.0, 65.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 164.0, 46.0, 237.0, 64.0 ]
				}

			}
, 			{
				"box" : 				{
					"bgmode" : 0,
					"border" : 0,
					"clickthrough" : 0,
					"embed" : 1,
					"enablehscroll" : 0,
					"enablevscroll" : 0,
					"id" : "obj-18",
					"lockeddragscroll" : 0,
					"lockedsize" : 0,
					"maxclass" : "bpatcher",
					"numinlets" : 0,
					"numoutlets" : 0,
					"offset" : [ 0.0, 0.0 ],
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 9,
							"minor" : 0,
							"revision" : 7,
							"architecture" : "x64",
							"modernui" : 1
						}
,
						"classnamespace" : "box",
						"rect" : [ 887.0, 223.0, 339.796188354492188, 148.313430786132812 ],
						"openrect" : [ 0.0, 0.0, 339.796188354492188, 148.313430786132812 ],
						"openinpresentation" : 1,
						"gridsize" : [ 15.0, 15.0 ],
						"boxes" : [ 							{
								"box" : 								{
									"id" : "obj-34",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 309.0, 61.0, 320.0, 20.0 ],
									"text" : "Bpatcher that stores gaussian and sinc grain envelopes"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-13",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"patching_rect" : [ 751.0, 114.0, 58.0, 22.0 ],
									"text" : "loadbang"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-10",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 752.0, 146.0, 61.0, 22.0 ],
									"text" : "fill sinc 20"
								}

							}
, 							{
								"box" : 								{
									"buffername" : "grainEnv2",
									"id" : "obj-8",
									"maxclass" : "waveform~",
									"numinlets" : 5,
									"numoutlets" : 6,
									"outlettype" : [ "float", "float", "float", "float", "list", "" ],
									"patching_rect" : [ 752.0, 221.0, 256.0, 64.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 0.0, 66.0, 256.0, 64.0 ]
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-4",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "float", "bang" ],
									"patching_rect" : [ 751.0, 182.0, 178.0, 22.0 ],
									"text" : "buffer~ grainEnv2 @samps 512"
								}

							}
, 							{
								"box" : 								{
									"buffername" : "grainEnv",
									"id" : "obj-7",
									"maxclass" : "waveform~",
									"numinlets" : 5,
									"numoutlets" : 6,
									"outlettype" : [ "float", "float", "float", "float", "list", "" ],
									"patching_rect" : [ 389.0, 226.0, 256.0, 64.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 0.0, 0.0, 256.0, 64.0 ]
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-5",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 389.0, 187.0, 75.0, 22.0 ],
									"text" : "set grainEnv"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-11",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "float", "bang" ],
									"patching_rect" : [ 309.0, 97.0, 171.0, 22.0 ],
									"text" : "buffer~ grainEnv @samps 512"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-1",
									"maxclass" : "newobj",
									"numinlets" : 3,
									"numoutlets" : 1,
									"outlettype" : [ "float" ],
									"patching_rect" : [ 318.0, 402.0, 92.0, 22.0 ],
									"text" : "peek~ grainEnv"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-2",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 318.0, 352.0, 57.0, 22.0 ],
									"text" : "pack 0 0."
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-3",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 356.0, 306.0, 302.0, 22.0 ],
									"text" : "expr exp(-0.5*pow(($i1-((512-1)/2))/(0.4*((512-1)/2))\\,2))"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-12",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 3,
									"outlettype" : [ "bang", "bang", "int" ],
									"patching_rect" : [ 309.0, 187.0, 47.0, 22.0 ],
									"text" : "uzi 512"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-14",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"patching_rect" : [ 309.0, 146.0, 58.0, 22.0 ],
									"text" : "loadbang"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"source" : [ "obj-10", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-2", 0 ],
									"order" : 1,
									"source" : [ "obj-12", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"order" : 0,
									"source" : [ "obj-12", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-10", 0 ],
									"source" : [ "obj-13", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-12", 0 ],
									"order" : 1,
									"source" : [ "obj-14", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-5", 0 ],
									"order" : 0,
									"source" : [ "obj-14", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-2", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-2", 1 ],
									"source" : [ "obj-3", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-7", 0 ],
									"source" : [ "obj-5", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 910.989055514335632, 763.736301064491272, 264.935062408447266, 133.766232490539551 ],
					"viewvisibility" : 1
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-65",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 115.764334559440613, 737.078710556030273, 345.45454216003418, 25.0 ],
					"text" : "note 135. 2.150328 0. 37.636706"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-63",
					"lastchannelcount" : 0,
					"maxclass" : "live.gain~",
					"numinlets" : 2,
					"numoutlets" : 5,
					"orientation" : 1,
					"outlettype" : [ "signal", "signal", "", "float", "list" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 88.41602623462677, 881.451619207859039, 125.0, 47.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 27.0, 92.0, 121.0, 47.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_initial" : [ -59.228346456692861 ],
							"parameter_initial_enable" : 1,
							"parameter_longname" : "live.gain~",
							"parameter_mmax" : 6.0,
							"parameter_mmin" : -70.0,
							"parameter_modmode" : 3,
							"parameter_shortname" : "live.gain~",
							"parameter_type" : 0,
							"parameter_unitstyle" : 4
						}

					}
,
					"varname" : "live.gain~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-62",
					"maxclass" : "ezdac~",
					"numinlets" : 2,
					"numoutlets" : 0,
					"patching_rect" : [ 93.254735946655273, 1004.838716864585876, 48.051947593688965, 48.051947593688965 ],
					"presentation" : 1,
					"presentation_rect" : [ 368.0, 161.555088607397096, 74.693432988109578, 74.693432988109578 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-58",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 67.93151759687953, 267.03298008441925, 74.0, 25.0 ],
					"text" : "metro 1000"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-54",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "signal", "signal" ],
					"patching_rect" : [ 92.631582260131836, 800.000063896179199, 235.0, 25.0 ],
					"text" : "poly~ violin-grain 200 @steal 1 @parallel 1",
					"varname" : "poly~_AA"
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"midpoints" : [ 1060.944494247436523, 645.579383015632629, 1047.0, 645.579383015632629, 1047.0, 675.579383015632629, 1060.944494247436523, 675.579383015632629 ],
					"order" : 1,
					"source" : [ "obj-12", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-42", 1 ],
					"order" : 0,
					"source" : [ "obj-12", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-4", 0 ],
					"source" : [ "obj-125", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-57", 0 ],
					"source" : [ "obj-13", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-64", 0 ],
					"source" : [ "obj-13", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-85", 0 ],
					"midpoints" : [ 829.589822053909302, 693.0, 563.466616749763489, 693.0 ],
					"source" : [ "obj-136", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 0 ],
					"source" : [ "obj-16", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-58", 1 ],
					"source" : [ "obj-17", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-31", 0 ],
					"source" : [ "obj-19", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-136", 0 ],
					"order" : 0,
					"source" : [ "obj-197", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-200", 0 ],
					"order" : 1,
					"source" : [ "obj-197", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-63", 1 ],
					"source" : [ "obj-202", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-26", 1 ],
					"order" : 0,
					"source" : [ "obj-25", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-26", 0 ],
					"order" : 1,
					"source" : [ "obj-25", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-85", 1 ],
					"midpoints" : [ 553.655838966369629, 693.0, 574.625707507133484, 693.0 ],
					"source" : [ "obj-26", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-167", 1 ],
					"midpoints" : [ 710.59893536567688, 390.173823744229594, 480.507839814716135, 390.173823744229594 ],
					"order" : 1,
					"source" : [ "obj-27", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-66", 0 ],
					"order" : 0,
					"source" : [ "obj-27", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-11", 0 ],
					"order" : 2,
					"source" : [ "obj-3", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-54", 0 ],
					"order" : 1,
					"source" : [ "obj-3", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-65", 1 ],
					"midpoints" : [ 101.668827056884766, 699.495735645294189, 447.963703513145447, 699.495735645294189, 447.963703513145447, 732.495735645294189, 451.718876719474792, 732.495735645294189 ],
					"order" : 0,
					"source" : [ "obj-3", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-85", 2 ],
					"midpoints" : [ 606.902591705322266, 702.0, 585.784798264503479, 702.0 ],
					"source" : [ "obj-30", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-49", 1 ],
					"source" : [ "obj-31", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-85", 3 ],
					"midpoints" : [ 661.44804573059082, 693.0, 596.943889021873474, 693.0 ],
					"source" : [ "obj-32", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-17", 0 ],
					"source" : [ "obj-33", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-37", 0 ],
					"source" : [ "obj-34", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-37", 0 ],
					"source" : [ "obj-35", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-15", 0 ],
					"order" : 0,
					"source" : [ "obj-36", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-202", 1 ],
					"midpoints" : [ 483.5, 841.123514456179691, 217.383558392524719, 841.123514456179691 ],
					"order" : 1,
					"source" : [ "obj-36", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-99", 1 ],
					"midpoints" : [ 483.5, 835.116375350829912, 111.765572428703308, 835.116375350829912 ],
					"order" : 2,
					"source" : [ "obj-36", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-27", 0 ],
					"source" : [ "obj-37", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-37", 0 ],
					"source" : [ "obj-38", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-36", 1 ],
					"source" : [ "obj-39", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-41", 0 ],
					"source" : [ "obj-40", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-36", 0 ],
					"source" : [ "obj-41", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-44", 0 ],
					"order" : 0,
					"source" : [ "obj-45", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-79", 0 ],
					"order" : 1,
					"source" : [ "obj-45", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-13", 0 ],
					"source" : [ "obj-46", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-85", 4 ],
					"midpoints" : [ 712.74674654006958, 693.0, 608.102979779243469, 693.0 ],
					"source" : [ "obj-48", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-202", 0 ],
					"midpoints" : [ 318.131582260131836, 846.495735645294189, 203.91602623462677, 846.495735645294189 ],
					"source" : [ "obj-54", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-43", 0 ],
					"order" : 0,
					"source" : [ "obj-54", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-99", 0 ],
					"midpoints" : [ 102.131582260131836, 846.495735645294189, 98.298040270805359, 846.495735645294189 ],
					"order" : 1,
					"source" : [ "obj-54", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-37", 0 ],
					"source" : [ "obj-57", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-72", 0 ],
					"source" : [ "obj-58", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-30", 1 ],
					"order" : 0,
					"source" : [ "obj-59", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-30", 0 ],
					"order" : 1,
					"source" : [ "obj-59", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-10", 0 ],
					"order" : 1,
					"source" : [ "obj-63", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-16", 0 ],
					"order" : 3,
					"source" : [ "obj-63", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-69", 0 ],
					"source" : [ "obj-63", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-70", 0 ],
					"order" : 2,
					"source" : [ "obj-63", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-78", 0 ],
					"order" : 0,
					"source" : [ "obj-63", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-34", 0 ],
					"source" : [ "obj-64", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-35", 0 ],
					"source" : [ "obj-64", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-62", 1 ],
					"source" : [ "obj-69", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-62", 0 ],
					"source" : [ "obj-70", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-75", 0 ],
					"source" : [ "obj-73", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-16", 0 ],
					"source" : [ "obj-74", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-77", 0 ],
					"source" : [ "obj-75", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-83", 1 ],
					"source" : [ "obj-77", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-73", 0 ],
					"source" : [ "obj-79", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-83", 0 ],
					"midpoints" : [ 325.983531951904297, 111.0, 303.0, 111.0, 303.0, 216.0, 306.203311204910278, 216.0 ],
					"source" : [ "obj-79", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 0 ],
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-5", 0 ],
					"source" : [ "obj-81", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-58", 0 ],
					"source" : [ "obj-83", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-84", 0 ],
					"source" : [ "obj-83", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-167", 0 ],
					"midpoints" : [ 563.466616749763489, 771.551895165976021, 38.467836493298819, 771.551895165976021, 38.467836493298819, 392.294546940669534, 82.567701935768127, 392.294546940669534 ],
					"order" : 1,
					"source" : [ "obj-85", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-36", 2 ],
					"midpoints" : [ 563.466616749763489, 757.024429798126221, 614.5, 757.024429798126221 ],
					"order" : 0,
					"source" : [ "obj-85", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-32", 1 ],
					"order" : 0,
					"source" : [ "obj-90", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-32", 0 ],
					"order" : 1,
					"source" : [ "obj-90", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-48", 1 ],
					"order" : 0,
					"source" : [ "obj-91", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-48", 0 ],
					"order" : 1,
					"source" : [ "obj-91", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-85", 0 ],
					"source" : [ "obj-92", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-63", 0 ],
					"source" : [ "obj-99", 0 ]
				}

			}
 ],
		"parameters" : 		{
			"obj-12" : [ "dial[4]", "dial", 0 ],
			"obj-125" : [ "number[6]", "number", 0 ],
			"obj-167::obj-22" : [ "slider", "slider", 0 ],
			"obj-167::obj-27" : [ "rslider", "rslider", 0 ],
			"obj-167::obj-46" : [ "number[1]", "number[1]", 0 ],
			"obj-167::obj-52" : [ "number", "number", 0 ],
			"obj-167::obj-82" : [ "rslider[1]", "rslider[1]", 0 ],
			"obj-25" : [ "dial[3]", "dial[3]", 0 ],
			"obj-33" : [ "number[3]", "number[3]", 0 ],
			"obj-45" : [ "radiogroup", "radiogroup", 0 ],
			"obj-54.100::obj-118" : [ "number[105]", "number[1]", 0 ],
			"obj-54.101::obj-118" : [ "number[106]", "number[1]", 0 ],
			"obj-54.102::obj-118" : [ "number[107]", "number[1]", 0 ],
			"obj-54.103::obj-118" : [ "number[108]", "number[1]", 0 ],
			"obj-54.104::obj-118" : [ "number[109]", "number[1]", 0 ],
			"obj-54.105::obj-118" : [ "number[110]", "number[1]", 0 ],
			"obj-54.106::obj-118" : [ "number[111]", "number[1]", 0 ],
			"obj-54.107::obj-118" : [ "number[112]", "number[1]", 0 ],
			"obj-54.108::obj-118" : [ "number[113]", "number[1]", 0 ],
			"obj-54.109::obj-118" : [ "number[114]", "number[1]", 0 ],
			"obj-54.10::obj-118" : [ "number[15]", "number[1]", 0 ],
			"obj-54.110::obj-118" : [ "number[115]", "number[1]", 0 ],
			"obj-54.111::obj-118" : [ "number[116]", "number[1]", 0 ],
			"obj-54.112::obj-118" : [ "number[117]", "number[1]", 0 ],
			"obj-54.113::obj-118" : [ "number[118]", "number[1]", 0 ],
			"obj-54.114::obj-118" : [ "number[119]", "number[1]", 0 ],
			"obj-54.115::obj-118" : [ "number[120]", "number[1]", 0 ],
			"obj-54.116::obj-118" : [ "number[121]", "number[1]", 0 ],
			"obj-54.117::obj-118" : [ "number[122]", "number[1]", 0 ],
			"obj-54.118::obj-118" : [ "number[123]", "number[1]", 0 ],
			"obj-54.119::obj-118" : [ "number[124]", "number[1]", 0 ],
			"obj-54.11::obj-118" : [ "number[16]", "number[1]", 0 ],
			"obj-54.120::obj-118" : [ "number[125]", "number[1]", 0 ],
			"obj-54.121::obj-118" : [ "number[126]", "number[1]", 0 ],
			"obj-54.122::obj-118" : [ "number[127]", "number[1]", 0 ],
			"obj-54.123::obj-118" : [ "number[128]", "number[1]", 0 ],
			"obj-54.124::obj-118" : [ "number[129]", "number[1]", 0 ],
			"obj-54.125::obj-118" : [ "number[130]", "number[1]", 0 ],
			"obj-54.126::obj-118" : [ "number[131]", "number[1]", 0 ],
			"obj-54.127::obj-118" : [ "number[132]", "number[1]", 0 ],
			"obj-54.128::obj-118" : [ "number[133]", "number[1]", 0 ],
			"obj-54.129::obj-118" : [ "number[134]", "number[1]", 0 ],
			"obj-54.12::obj-118" : [ "number[17]", "number[1]", 0 ],
			"obj-54.130::obj-118" : [ "number[135]", "number[1]", 0 ],
			"obj-54.131::obj-118" : [ "number[136]", "number[1]", 0 ],
			"obj-54.132::obj-118" : [ "number[137]", "number[1]", 0 ],
			"obj-54.133::obj-118" : [ "number[138]", "number[1]", 0 ],
			"obj-54.134::obj-118" : [ "number[139]", "number[1]", 0 ],
			"obj-54.135::obj-118" : [ "number[140]", "number[1]", 0 ],
			"obj-54.136::obj-118" : [ "number[141]", "number[1]", 0 ],
			"obj-54.137::obj-118" : [ "number[142]", "number[1]", 0 ],
			"obj-54.138::obj-118" : [ "number[143]", "number[1]", 0 ],
			"obj-54.139::obj-118" : [ "number[144]", "number[1]", 0 ],
			"obj-54.13::obj-118" : [ "number[18]", "number[1]", 0 ],
			"obj-54.140::obj-118" : [ "number[145]", "number[1]", 0 ],
			"obj-54.141::obj-118" : [ "number[146]", "number[1]", 0 ],
			"obj-54.142::obj-118" : [ "number[147]", "number[1]", 0 ],
			"obj-54.143::obj-118" : [ "number[148]", "number[1]", 0 ],
			"obj-54.144::obj-118" : [ "number[149]", "number[1]", 0 ],
			"obj-54.145::obj-118" : [ "number[150]", "number[1]", 0 ],
			"obj-54.146::obj-118" : [ "number[151]", "number[1]", 0 ],
			"obj-54.147::obj-118" : [ "number[152]", "number[1]", 0 ],
			"obj-54.148::obj-118" : [ "number[153]", "number[1]", 0 ],
			"obj-54.149::obj-118" : [ "number[154]", "number[1]", 0 ],
			"obj-54.14::obj-118" : [ "number[19]", "number[1]", 0 ],
			"obj-54.150::obj-118" : [ "number[155]", "number[1]", 0 ],
			"obj-54.151::obj-118" : [ "number[156]", "number[1]", 0 ],
			"obj-54.152::obj-118" : [ "number[157]", "number[1]", 0 ],
			"obj-54.153::obj-118" : [ "number[158]", "number[1]", 0 ],
			"obj-54.154::obj-118" : [ "number[159]", "number[1]", 0 ],
			"obj-54.155::obj-118" : [ "number[160]", "number[1]", 0 ],
			"obj-54.156::obj-118" : [ "number[161]", "number[1]", 0 ],
			"obj-54.157::obj-118" : [ "number[162]", "number[1]", 0 ],
			"obj-54.158::obj-118" : [ "number[163]", "number[1]", 0 ],
			"obj-54.159::obj-118" : [ "number[164]", "number[1]", 0 ],
			"obj-54.15::obj-118" : [ "number[20]", "number[1]", 0 ],
			"obj-54.160::obj-118" : [ "number[165]", "number[1]", 0 ],
			"obj-54.161::obj-118" : [ "number[166]", "number[1]", 0 ],
			"obj-54.162::obj-118" : [ "number[167]", "number[1]", 0 ],
			"obj-54.163::obj-118" : [ "number[168]", "number[1]", 0 ],
			"obj-54.164::obj-118" : [ "number[169]", "number[1]", 0 ],
			"obj-54.165::obj-118" : [ "number[170]", "number[1]", 0 ],
			"obj-54.166::obj-118" : [ "number[171]", "number[1]", 0 ],
			"obj-54.167::obj-118" : [ "number[172]", "number[1]", 0 ],
			"obj-54.168::obj-118" : [ "number[173]", "number[1]", 0 ],
			"obj-54.169::obj-118" : [ "number[174]", "number[1]", 0 ],
			"obj-54.16::obj-118" : [ "number[21]", "number[1]", 0 ],
			"obj-54.170::obj-118" : [ "number[175]", "number[1]", 0 ],
			"obj-54.171::obj-118" : [ "number[176]", "number[1]", 0 ],
			"obj-54.172::obj-118" : [ "number[177]", "number[1]", 0 ],
			"obj-54.173::obj-118" : [ "number[178]", "number[1]", 0 ],
			"obj-54.174::obj-118" : [ "number[179]", "number[1]", 0 ],
			"obj-54.175::obj-118" : [ "number[180]", "number[1]", 0 ],
			"obj-54.176::obj-118" : [ "number[181]", "number[1]", 0 ],
			"obj-54.177::obj-118" : [ "number[182]", "number[1]", 0 ],
			"obj-54.178::obj-118" : [ "number[183]", "number[1]", 0 ],
			"obj-54.179::obj-118" : [ "number[184]", "number[1]", 0 ],
			"obj-54.17::obj-118" : [ "number[22]", "number[1]", 0 ],
			"obj-54.180::obj-118" : [ "number[185]", "number[1]", 0 ],
			"obj-54.181::obj-118" : [ "number[186]", "number[1]", 0 ],
			"obj-54.182::obj-118" : [ "number[187]", "number[1]", 0 ],
			"obj-54.183::obj-118" : [ "number[188]", "number[1]", 0 ],
			"obj-54.184::obj-118" : [ "number[189]", "number[1]", 0 ],
			"obj-54.185::obj-118" : [ "number[190]", "number[1]", 0 ],
			"obj-54.186::obj-118" : [ "number[191]", "number[1]", 0 ],
			"obj-54.187::obj-118" : [ "number[192]", "number[1]", 0 ],
			"obj-54.188::obj-118" : [ "number[193]", "number[1]", 0 ],
			"obj-54.189::obj-118" : [ "number[194]", "number[1]", 0 ],
			"obj-54.18::obj-118" : [ "number[23]", "number[1]", 0 ],
			"obj-54.190::obj-118" : [ "number[195]", "number[1]", 0 ],
			"obj-54.191::obj-118" : [ "number[196]", "number[1]", 0 ],
			"obj-54.192::obj-118" : [ "number[197]", "number[1]", 0 ],
			"obj-54.193::obj-118" : [ "number[198]", "number[1]", 0 ],
			"obj-54.194::obj-118" : [ "number[199]", "number[1]", 0 ],
			"obj-54.195::obj-118" : [ "number[200]", "number[1]", 0 ],
			"obj-54.196::obj-118" : [ "number[201]", "number[1]", 0 ],
			"obj-54.197::obj-118" : [ "number[202]", "number[1]", 0 ],
			"obj-54.198::obj-118" : [ "number[203]", "number[1]", 0 ],
			"obj-54.199::obj-118" : [ "number[204]", "number[1]", 0 ],
			"obj-54.19::obj-118" : [ "number[24]", "number[1]", 0 ],
			"obj-54.1::obj-118" : [ "number[206]", "number[1]", 0 ],
			"obj-54.200::obj-118" : [ "number[205]", "number[1]", 0 ],
			"obj-54.20::obj-118" : [ "number[25]", "number[1]", 0 ],
			"obj-54.21::obj-118" : [ "number[26]", "number[1]", 0 ],
			"obj-54.22::obj-118" : [ "number[27]", "number[1]", 0 ],
			"obj-54.23::obj-118" : [ "number[28]", "number[1]", 0 ],
			"obj-54.24::obj-118" : [ "number[29]", "number[1]", 0 ],
			"obj-54.25::obj-118" : [ "number[30]", "number[1]", 0 ],
			"obj-54.26::obj-118" : [ "number[31]", "number[1]", 0 ],
			"obj-54.27::obj-118" : [ "number[32]", "number[1]", 0 ],
			"obj-54.28::obj-118" : [ "number[33]", "number[1]", 0 ],
			"obj-54.29::obj-118" : [ "number[34]", "number[1]", 0 ],
			"obj-54.2::obj-118" : [ "number[7]", "number[1]", 0 ],
			"obj-54.30::obj-118" : [ "number[35]", "number[1]", 0 ],
			"obj-54.31::obj-118" : [ "number[36]", "number[1]", 0 ],
			"obj-54.32::obj-118" : [ "number[37]", "number[1]", 0 ],
			"obj-54.33::obj-118" : [ "number[38]", "number[1]", 0 ],
			"obj-54.34::obj-118" : [ "number[39]", "number[1]", 0 ],
			"obj-54.35::obj-118" : [ "number[40]", "number[1]", 0 ],
			"obj-54.36::obj-118" : [ "number[41]", "number[1]", 0 ],
			"obj-54.37::obj-118" : [ "number[42]", "number[1]", 0 ],
			"obj-54.38::obj-118" : [ "number[43]", "number[1]", 0 ],
			"obj-54.39::obj-118" : [ "number[44]", "number[1]", 0 ],
			"obj-54.3::obj-118" : [ "number[8]", "number[1]", 0 ],
			"obj-54.40::obj-118" : [ "number[45]", "number[1]", 0 ],
			"obj-54.41::obj-118" : [ "number[46]", "number[1]", 0 ],
			"obj-54.42::obj-118" : [ "number[47]", "number[1]", 0 ],
			"obj-54.43::obj-118" : [ "number[48]", "number[1]", 0 ],
			"obj-54.44::obj-118" : [ "number[49]", "number[1]", 0 ],
			"obj-54.45::obj-118" : [ "number[50]", "number[1]", 0 ],
			"obj-54.46::obj-118" : [ "number[51]", "number[1]", 0 ],
			"obj-54.47::obj-118" : [ "number[52]", "number[1]", 0 ],
			"obj-54.48::obj-118" : [ "number[53]", "number[1]", 0 ],
			"obj-54.49::obj-118" : [ "number[54]", "number[1]", 0 ],
			"obj-54.4::obj-118" : [ "number[9]", "number[1]", 0 ],
			"obj-54.50::obj-118" : [ "number[55]", "number[1]", 0 ],
			"obj-54.51::obj-118" : [ "number[56]", "number[1]", 0 ],
			"obj-54.52::obj-118" : [ "number[57]", "number[1]", 0 ],
			"obj-54.53::obj-118" : [ "number[58]", "number[1]", 0 ],
			"obj-54.54::obj-118" : [ "number[59]", "number[1]", 0 ],
			"obj-54.55::obj-118" : [ "number[60]", "number[1]", 0 ],
			"obj-54.56::obj-118" : [ "number[61]", "number[1]", 0 ],
			"obj-54.57::obj-118" : [ "number[62]", "number[1]", 0 ],
			"obj-54.58::obj-118" : [ "number[63]", "number[1]", 0 ],
			"obj-54.59::obj-118" : [ "number[64]", "number[1]", 0 ],
			"obj-54.5::obj-118" : [ "number[10]", "number[1]", 0 ],
			"obj-54.60::obj-118" : [ "number[65]", "number[1]", 0 ],
			"obj-54.61::obj-118" : [ "number[66]", "number[1]", 0 ],
			"obj-54.62::obj-118" : [ "number[67]", "number[1]", 0 ],
			"obj-54.63::obj-118" : [ "number[68]", "number[1]", 0 ],
			"obj-54.64::obj-118" : [ "number[69]", "number[1]", 0 ],
			"obj-54.65::obj-118" : [ "number[70]", "number[1]", 0 ],
			"obj-54.66::obj-118" : [ "number[71]", "number[1]", 0 ],
			"obj-54.67::obj-118" : [ "number[72]", "number[1]", 0 ],
			"obj-54.68::obj-118" : [ "number[73]", "number[1]", 0 ],
			"obj-54.69::obj-118" : [ "number[74]", "number[1]", 0 ],
			"obj-54.6::obj-118" : [ "number[11]", "number[1]", 0 ],
			"obj-54.70::obj-118" : [ "number[75]", "number[1]", 0 ],
			"obj-54.71::obj-118" : [ "number[76]", "number[1]", 0 ],
			"obj-54.72::obj-118" : [ "number[77]", "number[1]", 0 ],
			"obj-54.73::obj-118" : [ "number[78]", "number[1]", 0 ],
			"obj-54.74::obj-118" : [ "number[79]", "number[1]", 0 ],
			"obj-54.75::obj-118" : [ "number[80]", "number[1]", 0 ],
			"obj-54.76::obj-118" : [ "number[81]", "number[1]", 0 ],
			"obj-54.77::obj-118" : [ "number[82]", "number[1]", 0 ],
			"obj-54.78::obj-118" : [ "number[83]", "number[1]", 0 ],
			"obj-54.79::obj-118" : [ "number[84]", "number[1]", 0 ],
			"obj-54.7::obj-118" : [ "number[12]", "number[1]", 0 ],
			"obj-54.80::obj-118" : [ "number[85]", "number[1]", 0 ],
			"obj-54.81::obj-118" : [ "number[86]", "number[1]", 0 ],
			"obj-54.82::obj-118" : [ "number[87]", "number[1]", 0 ],
			"obj-54.83::obj-118" : [ "number[88]", "number[1]", 0 ],
			"obj-54.84::obj-118" : [ "number[89]", "number[1]", 0 ],
			"obj-54.85::obj-118" : [ "number[90]", "number[1]", 0 ],
			"obj-54.86::obj-118" : [ "number[91]", "number[1]", 0 ],
			"obj-54.87::obj-118" : [ "number[92]", "number[1]", 0 ],
			"obj-54.88::obj-118" : [ "number[93]", "number[1]", 0 ],
			"obj-54.89::obj-118" : [ "number[94]", "number[1]", 0 ],
			"obj-54.8::obj-118" : [ "number[13]", "number[1]", 0 ],
			"obj-54.90::obj-118" : [ "number[95]", "number[1]", 0 ],
			"obj-54.91::obj-118" : [ "number[96]", "number[1]", 0 ],
			"obj-54.92::obj-118" : [ "number[97]", "number[1]", 0 ],
			"obj-54.93::obj-118" : [ "number[98]", "number[1]", 0 ],
			"obj-54.94::obj-118" : [ "number[99]", "number[1]", 0 ],
			"obj-54.95::obj-118" : [ "number[100]", "number[1]", 0 ],
			"obj-54.96::obj-118" : [ "number[101]", "number[1]", 0 ],
			"obj-54.97::obj-118" : [ "number[102]", "number[1]", 0 ],
			"obj-54.98::obj-118" : [ "number[103]", "number[1]", 0 ],
			"obj-54.99::obj-118" : [ "number[104]", "number[1]", 0 ],
			"obj-54.9::obj-118" : [ "number[14]", "number[1]", 0 ],
			"obj-59" : [ "dial[2]", "dial[2]", 0 ],
			"obj-63" : [ "live.gain~", "live.gain~", 0 ],
			"obj-72::obj-12" : [ "slider[2]", "slider[2]", 0 ],
			"obj-72::obj-5" : [ "number[5]", "number[1]", 0 ],
			"obj-72::obj-7" : [ "slider[4]", "slider[1]", 0 ],
			"obj-72::obj-94" : [ "slider[3]", "slider", 0 ],
			"obj-81" : [ "toggle", "toggle", 0 ],
			"obj-90" : [ "dial[1]", "dial[1]", 0 ],
			"obj-91" : [ "dial", "dial", 0 ],
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
, 			{
				"name" : "cloud.maxpat",
				"bootpath" : "~/git/instruments/group-1/granular-synth/patchers",
				"patcherrelativepath" : ".",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "pan2.maxpat",
				"bootpath" : "~/git/instruments/group-1/granular-synth/patchers",
				"patcherrelativepath" : ".",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "serial-to-max.maxpat",
				"bootpath" : "~/git/instruments/group-1/granular-synth/patchers",
				"patcherrelativepath" : ".",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "single-grain-parameters.maxpat",
				"bootpath" : "~/git/instruments/group-1/granular-synth/patchers",
				"patcherrelativepath" : ".",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "violin-grain.maxpat",
				"bootpath" : "~/git/instruments/group-1/granular-synth/patchers",
				"patcherrelativepath" : ".",
				"type" : "JSON",
				"implicit" : 1
			}
 ],
		"autosave" : 0,
		"boxgroups" : [ 			{
				"boxes" : [ "obj-45", "obj-50" ]
			}
, 			{
				"boxes" : [ "obj-18", "obj-88" ]
			}
, 			{
				"boxes" : [ "obj-48", "obj-32", "obj-30", "obj-26", "obj-90", "obj-91", "obj-59", "obj-25", "obj-53", "obj-89", "obj-55", "obj-56", "obj-105" ]
			}
, 			{
				"boxes" : [ "obj-125", "obj-81", "obj-122", "obj-127", "obj-76" ]
			}
 ]
	}

}
