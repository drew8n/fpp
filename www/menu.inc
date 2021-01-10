<?php

$kernel_version = exec("uname -r");

$fpp_head_version = "v" . getFPPVersion();
$git_branch = getFPPBranch();

if (!preg_match("/^$git_branch(-.*)?$/", $fpp_head_version))
	$fpp_head_version .= " ($git_branch branch)";

?>

<?php require_once(dirname(__FILE__)."/config.php"); ?>
<?php
function list_plugin_entries($menu)
{
	global $pluginDirectory;
	if ( $menu && file_exists($pluginDirectory))
	{
		$handle = opendir($pluginDirectory);
		if ( $handle )
		{
			$first = 1;
			while (($plugin = readdir($handle)) !== false)
			{
				if (!in_array($plugin, array('.', '..')))
				{
					// Old naming convention ${MENU}_menu.inc
					if ( file_exists($pluginDirectory."/".$plugin."/".$menu."_menu.inc") )
					{
						if ($first)
						{
							$first = 0;
							echo "<li><b><font color='white' size=-1>- - - - - - - Plugins - - - - - - -</font></b></li>\n";
						}

						-include_once($pluginDirectory."/".$plugin."/".$menu."_menu.inc");
					}

					// New single menu.inc file which has some logic in it to display relevant menus.
					// See the example in the fpp-plugin-Template plugin
					if ( file_exists($pluginDirectory."/".$plugin."/menu.inc") )
					{
						if ($first)
						{
							$first = 0;
							echo "<li><b><font color='white' size=-1>- - - - - - - Plugins - - - - - - -</font></b></li>\n";
						}

						-include($pluginDirectory."/".$plugin."/menu.inc");
					}
				}
			}
		}
	}
}
?>

<nav class="navbar navbar-transparent bg-dark navbar-color-on-scroll fixed-top navbar-expand-lg"
        color-on-scroll="20" id="sectionsNav">
        <div class="container">
            <div class="navbar-translate d-flex">
                <img src="falconlogoinverse.png" alt="" height="50" class="d-inline-block align-top" />
                <span class="ml-3">
                    <a class="navbar-brand navtitle" href="#">
                        <? echo $settings['Title']; ?>
                    </a><br />
                    <small class="navsubtitle">Version: <a href='about.php' class='nonULLink headerLink'><?php echo $fpp_head_version; ?></a> &middot; 
                    <br/>Host: <?
    if (!file_exists("/etc/fpp/desktop")) {
        echo "<a href='networkconfig.php' class='nonULLink headerLink'>" . $settings['HostName'] . "</a> " ;
    } else {
        echo "" . gethostname() . "&nbsp;";
    }

    echo("(<span id=\"header_IPs\"></span>)");
    ?></small>
                </span>
                <button class="navbar-toggler" type="button" data-toggle="collapse" aria-expanded="false"
                    aria-label="Toggle navigation">
                    <span class="sr-only">Toggle navigation</span>
                    <span class="navbar-toggler-icon"></span>
                    <span class="navbar-toggler-icon"></span>
                    <span class="navbar-toggler-icon"></span>
                </button>
            </div>
            <div class="collapse navbar-collapse">
                <ul class="navbar-nav ml-auto">
                    <li class="dropdown nav-item">
                        <a href="#" class="dropdown-toggle nav-link" data-toggle="dropdown">
                            <!--<i class="material-icons">apps</i>--> Status/Control
                        </a>
                        <div class="dropdown-menu dropdown-with-icons">
                            <a class="dropdown-item active" href="index.php">Status Page</a>
                            <?
if (!file_exists("/etc/fpp/desktop")) {
          echo '<a class="dropdown-item active" href="networkconfig.php">Network</a>';
}
?>
                            <a class="dropdown-item" href="multisync.php">Multi Sync</a>
                            <a class="dropdown-item" href="settings.php">FPP Settings</a>
                            <a class="dropdown-item" href="backup.php">FPP Backup</a>
                            <a class="dropdown-item" href="proxies.php">Proxy Settings</a>
                            <a class="dropdown-item" href="events.php">Events</a>
                            <a class="dropdown-item" href="effects.php">Effects</a>
                            <a class="dropdown-item" href="testing.php">Display Testing</a>
                            <?
          if (file_exists($settings['co-other'])) {
            $js = json_decode(file_get_contents($settings['co-other']), true);
            foreach($js["channelOutputs"] as $key => $val) {
                if (($val["enabled"] == 1) && ($val["type"] == "HTTPVirtualDisplay")) {
                echo "<a class='dropdown-item' href='virtualdisplaywrapper.php'>Virtual Display</a>";
                }
            }
          
          }
          ?>
          <div class="dropdown-divider"></div>
          <?php list_plugin_entries("status"); ?>
                        </div>
                    </li>
                    <li class="dropdown nav-item">
                        <a href="#" class="dropdown-toggle nav-link" data-toggle="dropdown">
                            Content Setup
                        </a>
                        <div class="dropdown-menu dropdown-with-icons">
                            <a class="dropdown-item" href="uploadfile.php">File Manager</a>
                            <a class="dropdown-item" href="playlists.php">Playlists</a>
                            <a class="dropdown-item" href="scheduler.php">Scheduler</a>
                            <a class="dropdown-item" href="scriptbrowser.php">Script Repository
                                Browser</a>
                            <a class="dropdown-item" href="plugins.php">Plugin Manager</a>
                            <?php list_plugin_entries("content"); ?>
                        </div>
                    </li>
                    <li class="dropdown nav-item">
                        <a href="#" class="dropdown-toggle nav-link" data-toggle="dropdown">
                            Input/Output Setup
                        </a>
                        <div class="dropdown-menu dropdown-with-icons">
                            <a class="dropdown-item" href="channelinputs.php">
                                Channel Inputs</a>
                            <a class="dropdown-item" href="channeloutputs.php">Channel Outputs</a>
                            <a class="dropdown-item" href="outputprocessors.php"><i class="fas fa-microchip"></i> Output Processors</a>
                            <a class="dropdown-item" href="pixeloverlaymodels.php"><i class="fas fa-cubes"></i> Pixel Overlay Models</a>
                            <a class="dropdown-item" href="gpio.php"><i class="fas fa-exchange-alt"></i> GPIO Inputs</a>
                            <?php list_plugin_entries("output"); ?>
                        </div>
                    </li>
                    <li class="dropdown nav-item">
                        <a href="#" class="dropdown-toggle nav-link" data-toggle="dropdown">
                            Help
                        </a>
                        <div class="dropdown-menu dropdown-with-icons">
                            <a class="dropdown-item" href="https://falconchristmas.github.io/FPP_Manual(4.6).pdf">FPP Manual</a>
                            <a class="dropdown-item" href="http://falconchristmas.com/wiki/index.php/Falcon_FPP">Wiki/Help</a>
                            <? if ($settings['uiLevel'] > 0) { ?>
          <a class="dropdown-item" href="apihelp.php">REST API Help</a>
<? } ?>
                            <a class="dropdown-item" href="cliHelp.php">fpp &amp; fppmm Usage</a>
                            <a class="dropdown-item" href="troubleshooting.php">Troubleshooting Commands</a>
                            <a class="dropdown-item" href="http://<?php echo $_SERVER['SERVER_ADDR'] ?>:4200" target="_new">SSH Shell</a>
                            <a class="dropdown-item" href="about.php">About</a>
                            <a class="dropdown-item" href="credits.php">Credits</a>
                            <?php list_plugin_entries("help"); ?>
                        </div>
                    </li>
                </ul>
            </div>
        </div>
    </nav>
    <div class="page-header header-filter clear-filter black-filter" data-parallax="true"
        style="background-image: url('bkgnd.jpg');">

    </div>


  <div style='float: right'><a href='#' class='nonULLink' onClick='ClearRestartFlag(); ClearRebootFlag();'><img src='images/1x1.png' width='5' height='5' style="vertical-align: top;"></a></div>

<?php

	if (file_exists("/etc/fpp/rfs_version") && exec('grep "^[^#].*/home/pi/media" /etc/fstab') )
	{
		$mounted = 0;
		$needToMount = 0;
		$mountPoints = file("/etc/fstab");
		foreach ($mountPoints as $mountPoint)
		{
			if (preg_match("/^[^#].*\/home\/[a-z]*\/media/", $mountPoint))
			{
				$needToMount = 1;
				$mounts = file("/proc/mounts");
				$mounted = 0;
				foreach ($mounts as $mount)
				{
					if (preg_match("/\/home\/[a-z]*\/media/", $mount))
					{
						$mounted = 1;
						break;
					}
				}

				break;
			}
		}


		if ($needToMount && !$mounted)
		{
?>
	<br><b><font color='#ff0000'>WARNING: <?= $fppHome; ?>/media is not mounted, is a USB flash drive inserted?</font></b>
<?
		}
	}
?>

    
  </div>

  <div id='restartFlag'><span class='inlineBlock'>Settings have changed. <br class='headerBreak'>FPPD Restart Required</span><span class='inlineBlock'>&nbsp;-&nbsp;</span><span class='inlineBlock'><input name="btnRestartFPPD" type="button" onClick="RestartFPPD();" class = "buttons" value="Restart FPPD">
<?
  if (basename($_SERVER['PHP_SELF']) == "developer.php")
  {
?>
  <input type='button' class = "buttons" value='Clear' onClick='ClearRestartFlag();'>
<?
  }
?>
    </span>
  </div>
<?  if (!file_exists("/opt/fpp/src/fppd")) { ?>
<div id='rebuildPopup' title='FPP Upgrade' style="display: none">
    <textarea style='width: 99%; height: 97%;' disabled id='rebuildText'>
    </textarea>
</div>
<script>
function RebuildFPPD() {
    $('#rebuildPopup').dialog({ height: 600, width: 900, title: "Rebuild FPP" });
    $('#rebuildPopup').dialog( "moveToTop" );
    $('#rebuildText').html('');
    StreamURL('manualUpdate.php?wrapped=1', 'rebuildText');
}
</script>
  <div id="compileFPPDBanner"><span class='inlineBlock'>FPPD not found. <br class='headerBreak'>Rebuild required</span><span class='inlineBlock'>&nbsp;-&nbsp;</span><span class='inlineBlock'><input name="btnRebuild" onClick="RebuildFPPD();" type="button" class = "buttons" value="Rebuild"></span></div>
<? } ?>
  <div id='unsupportedBrowser'>FPP will not work with this browser.  Chrome, Firefox, or Edge is strongly recommended.</div>
  <div id='rebootFlag'><span class='inlineBlock'>Base configuration has changed. <br class='headerBreak'>Reboot Required</span><span>&nbsp;-&nbsp;</span><span class='inlineBlock'><input name="btnReboot" onClick="RebootPi();" type="button" class = "buttons" value="Reboot">
<?
  if (basename($_SERVER['PHP_SELF']) == "developer.php")
  {
?>
  <input type='button' class = "buttons" value='Clear' onClick='ClearRebootFlag();'>
<?
  }
?>
    </span>
  </div>

      <!--<div class='helpLinkDiv'><a href='javascript:void();' onClick='DisplayHelp();' class='nonULLink'>&nbsp;Press F1 for help&nbsp;&nbsp;</a></div>-->

<script language="Javascript">
function handleKeypress(e) {
	if(e.keyCode == 112) {
		e.preventDefault();
		DisplayHelp();
	}
};

function CheckBrowser() {
    var ua = window.navigator.userAgent;
    var msie = ua.indexOf('MSIE '); // IE<11
    var trident = ua.indexOf('Trident/'); // IE11
    if (msie > 0 || trident > 0) {
       // IE 10 or older => return version number
        $('#unsupportedBrowser').show();
    } else {
        $('#unsupportedBrowser').hide();
    }
    if(navigator.userAgent.indexOf('Mac') > 0) {
        $('body').addClass('mac-os');
    }
}

$(document).ready(function() {
	CheckBrowser();
	LoadNetworkDetails();
	$(document).on('keydown', handleKeypress);

	CheckRestartRebootFlags();
});

</script>

