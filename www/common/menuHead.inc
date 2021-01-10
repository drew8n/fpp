
	<!-- jquery -->
	<script type="text/javascript" src="js/jquery-latest.min.js"></script>
	<script type="text/javascript" src="js/jquery-ui.min.js"></script>
	<script type="text/javascript" src="js/jquery.ui.touch-punch.js"></script>
	<script type="text/javascript" src="js/jquery.jgrowl.min.js"></script>
	<link rel="stylesheet" href="css/jquery-ui.css" />
	<link rel="stylesheet" href="css/jquery.jgrowl.min.css" />
	<!--<link rel="stylesheet" href="css/classicTheme/style.css" media="all" />-->
 
 
    <!--
       Font Awesome Free 5.13.0 by @fontawesome - https://fontawesome.com
       License - https://fontawesome.com/license/free (Icons: CC BY 4.0, Fonts: SIL OFL 1.1, Code: MIT License)
    -->
    <!--<script type="text/javascript" src="js/fontawesome.min.js"></script>
    <script type="text/javascript" src="js/fontawesome-solid.min.js"></script>
    <link rel="stylesheet" href="css/fontawesome-solid.min.css" />-->

	<!-- finally FPP stuff, here so our CSS is last so we can override anything above -->
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<link rel="stylesheet" href="css/fpp.css?ref=<?php echo filemtime('css/fpp.css'); ?>" />
<? if (file_exists("/home/fpp/media/config/custom.css")) { ?>
    <link rel="stylesheet" href="api/configfile/custom.css?ref=<?php echo filemtime('/home/fpp/media/config/custom.css'); ?>" />
<? } ?>
    <script type="text/javascript" src="js/fpp.js?ref=<?php echo filemtime('js/fpp.js'); ?>"></script>
<? if (file_exists("/home/fpp/media/config/custom.js")) { ?>
    <script type="text/javascript" src="api/configfile/custom.js?ref=<?php echo filemtime('/home/fpp/media/config/custom.js'); ?>"></script>
<? } ?>

	<!-- menu -->
	<link href="jquery/smartmenus/src/css/sm-core-css.css" rel="stylesheet" type="text/css" />
	<link href="jquery/smartmenus/src/css/sm-clean/sm-clean.css" rel="stylesheet" type="text/css" />
	<script type="text/javascript" src="jquery/smartmenus/src/jquery.smartmenus.js"></script>

	<script type="text/javascript">
	$(function() {
		$('#fppMenu').smartmenus({subMenusMinWidth: "50%", showOnClick: true,
			showFunction: function($ul, complete) { $ul.slideDown(250, complete); },
			hideFunction: function($ul, complete) { $ul.slideUp(250, complete); },
		});
	});
	</script>

<?
	if (isset($settings['backgroundColor']) && $settings['backgroundColor'] != "")
	{
?>
		<style>
			#bodyWrapper {
				border: 50px;
				border-style: solid;
				border-color: #<? echo $settings['backgroundColor'] ?>;
			}
		</style>
<?
	}
?>

<meta name="viewport" content="width=device-width, initial-scale=1">


    <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.8.2/css/all.css">
    <link rel="stylesheet" type="text/css"
        href="https://fonts.googleapis.com/css?family=Roboto:300,400,500,700|Roboto+Slab:400,700|Material+Icons" />

    <!-- CSS Files -->
    <link href="assets/css/material-kit.css?v=2.0.7" rel="stylesheet" />
    <script src="assets/js/core/jquery.min.js" type="text/javascript"></script>
    <script src="assets/js/core/popper.min.js" type="text/javascript"></script>
    <script src="assets/js/core/bootstrap-material-design.min.js" type="text/javascript"></script>
    <script src="assets/js/plugins/moment.min.js"></script>
    <!--	Plugin for the Datepicker, full documentation here: https://github.com/Eonasdan/bootstrap-datetimepicker -->
    <script src="assets/js/plugins/bootstrap-datetimepicker.js" type="text/javascript"></script>
    <!--  Plugin for the Sliders, full documentation here: http://refreshless.com/nouislider/ -->
    <script src="assets/js/plugins/nouislider.min.js" type="text/javascript"></script>
    <!-- Control Center for Material Kit: parallax effects, scripts for the example pages etc -->
    <script src="assets/js/material-kit.js?v=2.0.7" type="text/javascript"></script>

    <style>
        .dropdown-item .fas {
            width: 20px;
            display: inline-block;
            text-align: center;
            padding-right: 4px;
        }

        .page-header {
            height: 125px;
        }

        .navtitle {
            padding-bottom: 0px !important;
            padding-top: 0px !important;
            height: 34px !important;
            line-height: 24px !important;
            font-size: 1.75rem !important;
        }

        .navsubtitle {
            color: white;
        }

        @media (max-width: 575.98px) {
            .nav7subtitle {
                display: none;
            }
        }

        .black-filter:after {
            background: rgba(0, 0, 0, 0.64);
            background: linear-gradient(45deg, rgba(24, 11, 34, 0.88) 0%, rgba(32, 13, 48, 0.45) 100%);
            background: -moz-linear-gradient(135deg, rgba(24, 11, 34, 0.88) 0%, rgba(32, 13, 48, 0.45) 100%);
            background: -webkit-linear-gradient(135deg, rgba(24, 11, 34, 0.88) 0%, rgba(32, 13, 48, 0.45) 100%);
        }



        @media (max-width: 1000px) {
            .navbar-collapse {
                box-shadow: 0 4px 8px 0 rgba(0, 0, 0, 0.2), 0 6px 20px 0 rgba(0, 0, 0, 0.19);

            }
        }

        body {
            font-size: 0.9rem;
        }

        .fascolor {
            color: #9c27b0;
        }

        .title {
            margin-top: 30px;
            margin-bottom: 0px;
            min-height: 10px;
        }

		.navsubtitle a{
			color:white;
		}

    </style>