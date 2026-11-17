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
		"openrect" : [ 0.0, 0.0, 416.940137878948008, 212.78366322119291 ],
		"openinpresentation" : 1,
		"default_fontname" : "Avenir",
		"gridsize" : [ 15.0, 15.0 ],
		"boxes" : [ 			{
				"box" : 				{
					"comment" : "Grain Pitch (midi)",
					"id" : "obj-24",
					"index" : 0,
					"maxclass" : "inlet",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 492.04544985294342, 117.045453429222107, 30.0, 30.0 ]
				}

			}
, 			{
				"box" : 				{
					"comment" : "Grain Bandwidth",
					"id" : "obj-21",
					"index" : 0,
					"maxclass" : "inlet",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 467.045450091362, 80.681817412376404, 30.0, 30.0 ]
				}

			}
, 			{
				"box" : 				{
					"comment" : "Grain Density",
					"id" : "obj-14",
					"index" : 0,
					"maxclass" : "inlet",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 212.499997973442078, 276.136361002922058, 30.0, 30.0 ]
				}

			}
, 			{
				"box" : 				{
					"comment" : "Grain Duration",
					"id" : "obj-1",
					"index" : 0,
					"maxclass" : "inlet",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 128.409089684486389, 237.499997735023499, 30.0, 30.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-41",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 418.181814193725586, 310.227269768714905, 50.0, 25.0 ],
					"text" : "60"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-39",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 318.181815147399902, 337.499996781349182, 68.181817531585693, 25.0 ],
					"text" : "11.868024"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-35",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 473.863631844520569, 423.863632321357727, 47.0, 25.0 ],
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
					"patching_rect" : [ 482.954540848731995, 348.863633036613464, 41.0, 25.0 ],
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
					"patching_rect" : [ 523.863631367683411, 388.636359930038452, 30.0, 25.0 ],
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
					"patching_rect" : [ 464.772722840309143, 388.636359930038452, 29.5, 25.0 ],
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
					"patching_rect" : [ 482.954540848731995, 314.772724270820618, 29.5, 25.0 ],
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
					"patching_rect" : [ 473.863631844520569, 457.954541087150574, 39.0, 25.0 ],
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
					"patching_rect" : [ 494.318177103996277, 152.272725820541382, 29.545454263687134, 117.045453429222107 ],
					"presentation" : 1,
					"presentation_rect" : [ 220.965425819158554, 68.181817770004272, 35.170586258172989, 140.157487750053406 ],
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
					"patching_rect" : [ 467.045450091362, 151.136362195014954, 22.727272510528564, 121.59090793132782 ],
					"presentation" : 1,
					"presentation_rect" : [ 164.4000024497509, 66.800000995397568, 40.800000607967377, 141.53930452466011 ],
					"size" : 48.0
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-9",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 390.909087181091309, 120.454544305801392, 68.666668713092804, 23.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 150.510881036520004, 42.045454382896423, 68.666668713092804, 23.0 ],
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
					"patching_rect" : [ 523.863631367683411, 123.863635182380676, 80.000002384185791, 23.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 220.965425819158554, 42.045454382896423, 80.000002384185791, 23.0 ],
					"text" : "Center Freq"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-16",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 379.545450925827026, 564.772721886634827, 153.24675178527832, 23.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 257.954542994499207, 134.09090781211853, 150.0, 23.0 ],
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
					"patching_rect" : [ 379.545450925827026, 588.636358022689819, 153.24675178527832, 25.974025726318359 ],
					"presentation" : 1,
					"presentation_rect" : [ 257.954542994499207, 167.045452952384949, 149.999998927116394, 25.531914710998535 ],
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
					"patching_rect" : [ 295.454542636871338, 497.727267980575562, 153.24675178527832, 23.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 257.954542994499207, 69.318181157112122, 150.0, 23.0 ],
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
					"patching_rect" : [ 295.454542636871338, 523.863631367683411, 153.24675178527832, 25.974025726318359 ],
					"presentation" : 1,
					"presentation_rect" : [ 257.954542994499207, 106.818180799484253, 149.999998927116394, 25.531914710998535 ],
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
					"patching_rect" : [ 34.090908765792847, 102.27272629737854, 153.519675016403198, 27.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 5.681818127632141, 10.294117450714111, 402.454193949699402, 27.0 ],
					"text" : "CLOUD PARAMETERS"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-6",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 211.363634347915649, 251.136361241340637, 129.545453310012817, 23.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 7.299270033836365, 95.181817770004272, 127.737225592136383, 23.0 ],
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
					"presentation_rect" : [ 6.975932776927948, 120.181817770004272, 53.246752738952637, 25.0 ],
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
					"presentation_rect" : [ 6.975932776927948, 68.181817770004272, 53.246752738952637, 25.0 ],
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
					"patching_rect" : [ 105.681817173957825, 212.499997973442078, 95.454544544219971, 23.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 6.975932776927948, 43.181817770004272, 102.27272629737854, 23.0 ],
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
					"destination" : [ "obj-46", 0 ],
					"midpoints" : [ 137.909089684486389, 587.86363685131073, 71.999999403953552, 587.86363685131073 ],
					"source" : [ "obj-1", 0 ]
				}

			}
, 			{
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
					"destination" : [ "obj-52", 0 ],
					"midpoints" : [ 221.999997973442078, 437.86363685131073, 224.272725224494934, 437.86363685131073 ],
					"source" : [ "obj-14", 0 ]
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
					"midpoints" : [ 476.545450091362, 296.86363685131073, 492.454540848731995, 296.86363685131073 ],
					"order" : 0,
					"source" : [ "obj-18", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-39", 1 ],
					"order" : 1,
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
					"destination" : [ "obj-18", 0 ],
					"source" : [ "obj-21", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-32", 0 ],
					"midpoints" : [ 503.818177103996277, 299.86363685131073, 468.727272748947144, 299.86363685131073, 468.727272748947144, 383.86363685131073, 474.272722840309143, 383.86363685131073 ],
					"order" : 1,
					"source" : [ "obj-22", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 0 ],
					"midpoints" : [ 503.818177103996277, 299.86363685131073, 534.727272748947144, 299.86363685131073, 534.727272748947144, 383.86363685131073, 533.363631367683411, 383.86363685131073 ],
					"order" : 0,
					"source" : [ "obj-22", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-41", 1 ],
					"midpoints" : [ 503.818177103996277, 296.86363685131073, 458.681814193725586, 296.86363685131073 ],
					"order" : 2,
					"source" : [ "obj-22", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-22", 0 ],
					"source" : [ "obj-24", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-27", 0 ],
					"midpoints" : [ 483.363631844520569, 494.86363685131073, 459.727272748947144, 494.86363685131073, 459.727272748947144, 482.86363685131073, 282.727272748947144, 482.86363685131073, 282.727272748947144, 518.86363685131073, 304.954542636871338, 518.86363685131073 ],
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
