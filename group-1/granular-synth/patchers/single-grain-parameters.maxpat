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
		"rect" : [ 101.0, 231.0, 644.0, 231.0 ],
		"openrect" : [ 0.0, 0.0, 643.606417119708567, 100.407100072747198 ],
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
					"patching_rect" : [ 258.498323559761047, 308.0, 117.0, 29.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 258.0, 62.0, 113.259176731109619, 22.949087381362915 ],
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
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 369.0, 170.0, 147.0, 39.0 ],
					"text" : "Add physical modelling\nparameters later"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-3",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 180.236246347427368, 582.0, 108.0, 25.0 ],
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
					"patching_rect" : [ 164.795408844947815, 59.420290350914001, 234.0, 27.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 9.0, 1.188405990600586, 619.0, 27.0 ],
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
					"patching_rect" : [ 213.426895260810852, 528.813571929931641, 150.0, 39.0 ],
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
					"patching_rect" : [ 212.048200607299805, 91.566268444061279, 150.0, 23.0 ],
					"text" : "Bang for new grain"
				}

			}
, 			{
				"box" : 				{
					"comment" : "Bang for new grain",
					"id" : "obj-1",
					"index" : 1,
					"maxclass" : "inlet",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 174.698801636695862, 86.746991157531738, 30.0, 30.0 ]
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
					"patching_rect" : [ 288.405799508094788, 384.057974219322205, 119.480518341064453, 23.376623153686523 ],
					"presentation" : 1,
					"presentation_rect" : [ 381.159423470497131, 65.978355646133423, 119.480518341064453, 23.376623153686523 ],
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
					"patching_rect" : [ 180.236246347427368, 498.550728797912598, 115.0, 25.0 ],
					"text" : "pack note 0. 0. 0. 0."
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-9",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 288.405799508094788, 347.826089859008789, 110.389609336853027, 39.0 ],
					"presentation" : 1,
					"presentation_linecount" : 2,
					"presentation_rect" : [ 381.159423470497131, 23.188405990600586, 110.389609336853027, 39.0 ],
					"text" : "grain envelope interpolation"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-8",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 313.04348087310791, 420.28985857963562, 110.389609336853027, 23.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 508.695656418800354, 36.934782862663269, 110.389609336853027, 23.0 ],
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
					"patching_rect" : [ 313.04348087310791, 444.927539944648743, 119.480518341064453, 23.376623153686523 ],
					"presentation" : 1,
					"presentation_rect" : [ 508.695656418800354, 61.572464227676392, 119.480518341064453, 23.376623153686523 ],
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
					"patching_rect" : [ 231.853395938873291, 242.028987526893616, 53.246752738952637, 25.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 142.028986692428589, 66.666667222976685, 53.246752738952637, 25.0 ],
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
					"patching_rect" : [ 261.803518891334534, 279.710147261619568, 110.389609336853027, 23.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 260.869567394256592, 30.434782862663269, 110.389609336853027, 23.0 ],
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
					"patching_rect" : [ 233.232090592384338, 220.028987526893616, 111.0, 23.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 142.028986692428589, 30.434782862663269, 111.0, 23.0 ],
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
		"boxgroups" : [ 			{
				"boxes" : [ "obj-12", "obj-124" ]
			}
 ]
	}

}
