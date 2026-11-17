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
		"rect" : [ 101.0, 231.0, 643.606417119708567, 100.407100072747198 ],
		"openrect" : [ 0.0, 0.0, 496.543587216061496, 81.514572247336218 ],
		"openinpresentation" : 1,
		"default_fontname" : "Avenir",
		"gridsize" : [ 15.0, 15.0 ],
		"boxes" : [ 			{
				"box" : 				{
					"floatoutput" : 1,
					"id" : "obj-12",
					"maxclass" : "slider",
					"min" : 48.0,
					"numinlets" : 1,
					"numoutlets" : 1,
					"orientation" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 249.0, 326.0, 117.0, 29.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 124.565216302871704, 56.025456309318542, 113.259176731109619, 22.949087381362915 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_initial" : [ 60 ],
							"parameter_initial_enable" : 1,
							"parameter_longname" : "slider[2]",
							"parameter_mmax" : 72.0,
							"parameter_mmin" : 48.0,
							"parameter_modmode" : 3,
							"parameter_shortname" : "slider[2]",
							"parameter_type" : 0
						}

					}
,
					"size" : 24.0,
					"varname" : "slider[2]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-10",
					"linecount" : 4,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 463.0, 260.0, 147.0, 72.0 ],
					"text" : "Add physical modelling\nparameters later\nvibrato start time and depth"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-3",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 180.0, 535.0, 108.0, 25.0 ],
					"text" : "s grain-parameters"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Avenir",
					"id" : "obj-93",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 165.0, 174.0, 234.0, 27.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 9.333333611488342, 1.188405990600586, 484.000014424324036, 27.0 ],
					"text" : "Single Grain Parameters"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-13",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 304.0, 528.0, 150.0, 39.0 ],
					"text" : "Values are initialized in inspector"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Avenir",
					"id" : "obj-11",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 212.0, 206.0, 150.0, 23.0 ],
					"text" : "Bang for new grain"
				}

			}
, 			{
				"box" : 				{
					"comment" : "Bang for new grain",
					"id" : "obj-1",
					"index" : 0,
					"maxclass" : "inlet",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 175.0, 202.0, 30.0, 30.0 ]
				}

			}
, 			{
				"box" : 				{
					"floatoutput" : 1,
					"id" : "obj-94",
					"maxclass" : "slider",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 281.0, 404.0, 119.480518341064453, 23.376623153686523 ],
					"presentation" : 1,
					"presentation_rect" : [ 246.0, 56.0, 119.480518341064453, 23.376623153686523 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_initial" : [ 0.0 ],
							"parameter_initial_enable" : 1,
							"parameter_longname" : "slider[3]",
							"parameter_mmax" : 1.0,
							"parameter_modmode" : 3,
							"parameter_shortname" : "slider",
							"parameter_type" : 0
						}

					}
,
					"size" : 1.0,
					"varname" : "slider"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-21",
					"maxclass" : "newobj",
					"numinlets" : 5,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 180.0, 498.550728797912598, 152.04348087310791, 25.0 ],
					"text" : "pack note 0. 0. 0. 0."
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-9",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 281.0, 368.0, 110.389609336853027, 23.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 246.0, 29.0, 126.0, 23.0 ],
					"text" : "envelope interp"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-8",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 313.0, 439.0, 110.389609336853027, 23.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 374.000011146068573, 29.0, 119.48050719499588, 23.0 ],
					"text" : "grain pan"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-7",
					"maxclass" : "slider",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 313.0, 463.0, 119.480518341064453, 23.376623153686523 ],
					"presentation" : 1,
					"presentation_rect" : [ 374.0, 56.0, 119.480518341064453, 23.376623153686523 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_initial" : [ 63 ],
							"parameter_initial_enable" : 1,
							"parameter_longname" : "slider[4]",
							"parameter_modmode" : 3,
							"parameter_shortname" : "slider[1]",
							"parameter_type" : 0
						}

					}
,
					"varname" : "slider[1]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-5",
					"maxclass" : "number",
					"minimum" : 0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 211.0, 260.0, 53.246752738952637, 25.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 7.0, 55.0, 53.246752738952637, 25.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_initial" : [ 500 ],
							"parameter_initial_enable" : 1,
							"parameter_invisible" : 1,
							"parameter_longname" : "number[5]",
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
					"id" : "obj-124",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 253.0, 298.0, 110.389609336853027, 23.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 126.0, 30.0, 110.389609336853027, 23.0 ],
					"text" : "grain pitch (midi)"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Avenir",
					"id" : "obj-123",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 213.0, 238.0, 111.0, 23.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 7.0, 30.0, 111.0, 23.0 ],
					"text" : "grain dur (ms)"
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-21", 0 ],
					"source" : [ "obj-1", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-21", 2 ],
					"source" : [ "obj-12", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-3", 0 ],
					"source" : [ "obj-21", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-21", 1 ],
					"source" : [ "obj-5", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-21", 4 ],
					"source" : [ "obj-7", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-21", 3 ],
					"source" : [ "obj-94", 0 ]
				}

			}
 ],
		"parameters" : 		{
			"obj-12" : [ "slider[2]", "slider[2]", 0 ],
			"obj-5" : [ "number[5]", "number[1]", 0 ],
			"obj-7" : [ "slider[4]", "slider[1]", 0 ],
			"obj-94" : [ "slider[3]", "slider", 0 ],
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
		"dependency_cache" : [  ],
		"autosave" : 0
	}

}
