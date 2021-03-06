<!DOCTYPE html>
<html>

<head>
    <?php
    require_once('config.php');
    require_once('common.php');
    include 'playlistEntryTypes.php';
    include 'common/menuHead.inc';
    ?>



    <script type="text/javascript" src="/jquery/jquery.tablesorter/jquery.tablesorter.js"></script>
    <script type="text/javascript" src="/jquery/jquery.tablesorter/jquery.tablesorter.widgets.js"></script>
    <script type="text/javascript" src="/jquery/jquery.tablesorter/parsers/parser-network.js"></script>

    <link rel="stylesheet" href="/jquery/jquery.tablesorter/css/theme.blue.css">

    <script>
        PlayEntrySelected = 0;
        PlaySectionSelected = '';

        $(function() {
            $('.playlistEntriesBody').on('mousedown', 'tr', function(event, ui) {
                $('#tblPlaylistDetails tbody tr').removeClass('playlistSelectedEntry');
                $(this).addClass('playlistSelectedEntry');
                PlayEntrySelected = parseInt($(this).attr('id').substr(11)) - 1;
                PlaySectionSelected = $(this).parent().attr('id').substr(11);
            });

            //        $('#playlistDetailsContents').resizable({
            //            "handles": "s"
            //        });

            $('#syncStatsTable').tablesorter({
                headers: {
                    1: {
                        sorter: 'ipAddress'
                    }
                },
                widthFixed: false,
                theme: 'blue',
                widgets: ['zebra', 'filter', 'staticRow'],
                widgetOptions: {
                    filter_hideFilters: true
                }
            });
        });
    </script>

    <title>
        <? echo $pageTitle; ?>
    </title>

    <script>
        function PageSetup() {
            //Store frequently elements in variables
            var slider = $('#slider');
            var rslider = $('#remoteVolumeSlider');
            //Call the Slider
            slider.slider({
                //Config
                range: "min",
                min: 1,
                //value: 35,
            });
            rslider.slider({
                //Config
                range: "min",
                min: 1,
                //value: 35,
            });


            slider.slider({
                stop: function(event, ui) {
                    var value = slider.slider('value');

                    SetSpeakerIndicator(value);
                    $('#volume').html(value);
                    $('#remoteVolume').html(value);
                    SetVolume(value);
                }
            });
            rslider.slider({
                stop: function(event, ui) {
                    var value = rslider.slider('value');

                    SetSpeakerIndicator(value);
                    $('#volume').html(value);
                    $('#remoteVolume').html(value);
                    SetVolume(value);
                }
            });
            $(document).tooltip({
                content: function() {
                    $('.ui-tooltip').hide();
                    var id = $(this).attr('id');
                    id = id.replace('_img', '_tip');
                    return $('#' + id).html();
                },
                hide: {
                    delay: 1000
                }
            });

        };

        function SetSpeakerIndicator(value) {
            var speaker = $('#speaker');
            var remoteSpeaker = $('#remoteSpeaker');

            if (value <= 5) {
                speaker.css('background-position', '0 0');
                remoteSpeaker.css('background-position', '0 0');
            } else if (value <= 25) {
                speaker.css('background-position', '0 -25px');
                remoteSpeaker.css('background-position', '0 -25px');
            } else if (value <= 75) {
                speaker.css('background-position', '0 -50px');
                remoteSpeaker.css('background-position', '0 -50px');
            } else {
                speaker.css('background-position', '0 -75px');
                remoteSpeaker.css('background-position', '0 -75px');
            };
        }

        function IncrementVolume() {
            var volume = parseInt($('#volume').html());
            volume += 1;
            if (volume > 100)
                volume = 100;
            $('#volume').html(volume);
            $('#remoteVolume').html(volume);
            $('#slider').slider('value', volume);
            $('#remoteVolumeSlider').slider('value', volume);
            SetSpeakerIndicator(volume);
            SetVolume(volume);
        }

        function DecrementVolume() {
            var volume = parseInt($('#volume').html());
            volume -= 1;
            if (volume < 0)
                volume = 0;
            $('#volume').html(volume);
            $('#remoteVolume').html(volume);
            $('#slider').slider('value', volume);
            $('#remoteVolumeSlider').slider('value', volume);
            SetSpeakerIndicator(volume);
            SetVolume(volume);
        }

        function PreviousPlaylistEntry() {
            var url = 'api/command/Prev Playlist Item';
            $.get(url)
                .done(function() {})
                .fail(function() {});
        }

        function NextPlaylistEntry() {
            var url = 'api/command/Next Playlist Item';
            $.get(url)
                .done(function() {})
                .fail(function() {});
        }
    </script>


</head>

<body onLoad="PageSetup();GetFPPDmode();PopulatePlaylists(true);GetFPPStatus();bindVisibilityListener();GetVolume();">
    <div id="bodyWrapper">
        <?php
        include 'menu.inc';
        ?>
        <div class="main main-raised">
            <div class="container">
                <div class="title">
                    <h3>Falcon Player - Status</h3>
                </div>
            </div>
            <br />
            <?php
            if (isset($settings["LastBlock"]) && $settings["LastBlock"] > 1000000 && $settings["LastBlock"] < 7400000) {
            ?>
                <div id='upgradeFlag' style='background-color:red'>SD card has unused space. Go to <a href="settings.php?tab=Storage">Storage Settings</a> to expand the file system or create a new storage partition.</div>
                <br>
            <?php
            }
            ?>
            <div id="programControl" class="settings">


                <!-- Main FPP Mode/status/time header w/ sensor info -->
                <div id='daemonControl' class='statusDiv'>
                    <div class='statusBoxLeft'>
                        <table class='statusTable'>
                            <tr>
                                <th>FPPD Mode:</th>
                                <td>
                                    <select id="selFPPDmode" onChange="SetFPPDmode();">
                                        <option id="optFPPDmode_Player" value="2">Player (Standalone)</option>
                                        <option id="optFPPDmode_Master" value="6">Player (Master)</option>
                                        <option id="optFPPDmode_Remote" value="8">Player (Remote)</option>
                                        <option id="optFPPDmode_Bridge" value="1">Bridge</option>
                                    </select>
                                    <input type="button" id="btnDaemonControl" class="btn btn-primary btn-sm" value="" onClick="ControlFPPD();">
                                </td>
                            </tr>
                            <tr>
                                <th>FPPD Status:</th>
                                <td id="daemonStatus"></td>
                            </tr>
                            <tr>
                                <th>FPP Time:</th>
                                <td id="fppTime"></td>
                            </tr>
                            <tr id="mqttRow">
                                <th>MQTT:</th>
                                <td id="mqttStatus"></td>
                            </tr>
                            <tr id="warningsRow">
                                <td colspan="4" id="warningsTd">
                                    <div id="warningsDiv"></div>
                                </td>
                            </tr>
                        </table>
                    </div>
                    <div class='statusBoxRight'>
                        <div id="sensorData">
                        </div>
                    </div>
                    <div class='clear'></div>
                    <hr>
                </div>

                <!-- Bridge Mode stats -->
                <div id="bridgeModeInfo">
                    <H3>E1.31/DDP/ArtNet Packets and Bytes Received</H3>
                    <table style='width: 100%' class='statusTable'>
                        <tr>
                            <td align='left'>
                                <input type='button' onClick='GetUniverseBytesReceived();' value='Update'>
                            </td>
                            <td align='right'>
                                <? PrintSettingCheckbox("E1.31 Live Update", "e131statsLiveUpdate", 0, 0, "1", "0"); ?> Live Update Stats
                            </td>
                        </tr>
                    </table>
                    <hr>
                    <div id="bridgeStatistics1"></div>
                    <div id="bridgeStatistics2"></div>
                    <div class="clear"></div>
                </div>

                <!-- Remote Mode info -->
                <div id="remoteModeInfo" class='statusDiv'>
                    <table class='statusTable'>
                        <tr>
                            <th>Master System:</th>
                            <td id='syncMaster'></td>
                        </tr>
                        <tr>
                            <th>Remote Status:</th>
                            <td id='txtRemoteStatus'></td>
                        </tr>
                        <tr>
                            <th>Sequence Filename:</th>
                            <td id='txtRemoteSeqFilename'></td>
                        </tr>
                        <tr>
                            <th>Media Filename:</th>
                            <td id='txtRemoteMediaFilename'></td>
                        </tr>
                        <tr>
                            <th>Volume [<span id='remoteVolume' class='volume'></span>]:</th>
                            <td>
                                <input type="button" class='volumeButton' value="-" onClick="DecrementVolume();">
                                <span id="remoteVolumeSlider"></span> <!-- the Slider -->
                                <input type="button" class='volumeButton' value="+" onClick="IncrementVolume();">
                                <span id='remoteSpeaker'></span> <!-- Volume -->
                            </td>
                        </tr>
                    </table>
                    <hr>

                    <span class='title'>MultiSync Packet Counts</span><br>
                    <table style='width: 100%' class='statusTable'>
                        <tr>
                            <td align='left'>
                                <input type='button' class="btn btn-primary btn-sm" onClick='GetMultiSyncStats();' value='Update' class='buttons'>
                                <input type='button' class="btn btn-primary btn-sm" onClick='ResetMultiSyncStats();' value='Reset' class='buttons'>
                            </td>
                            <td align='right'>
                                <? PrintSettingCheckbox("MultiSync Stats Live Update", "syncStatsLiveUpdate", 0, 0, "1", "0"); ?> Live Update Stats
                            </td>
                        </tr>
                    </table>
                    <div class='fppTableWrapper'>
                        <div class='fppTableContents'>
                            <table id='syncStatsTable'>
                                <thead>
                                    <tr>
                                        <th rowspan=2>Host</th>
                                        <th rowspan=2>Last Received</th>
                                        <th colspan=4 class="sorter-false">Sequence Sync</th>
                                        <th colspan=4 class="sorter-false">Media Sync</th>
                                        <th rowspan=2>Blank<br>Data</th>
                                        <th rowspan=2>Ping</th>
                                        <th rowspan=2>Plugin</th>
                                        <th rowspan=2>FPP<br>Command</th>
                                        <th rowspan=2>Event</th>
                                        <th rowspan=2>Errors</th>
                                    </tr>
                                    <tr>
                                        <th>Open</th>
                                        <th>Start</th>
                                        <th>Stop</th>
                                        <th>Sync</th>
                                        <th>Open</th>
                                        <th>Start</th>
                                        <th>Stop</th>
                                        <th>Sync</th>
                                    </tr>
                                </thead>
                                <tbody id='syncStats'>
                                </tbody>
                            </table>
                        </div>
                    </div>
                </div>

                <!-- Player/Master Mode Info -->
                <div id="playerModeInfo" class='statusDiv'>
                    <div id='schedulerInfo'>
                        <div class='statusBoxLeft'>
                            <table class='statusTable'>
                                <tr>
                                    <th>Scheduler Status:</th>
                                    <td><span id='schedulerStatus'></span>
                                        &nbsp;&nbsp;<input type='button' class='btn btn-primary btn-sm wideButton' onClick='PreviewSchedule();' value='View Schedule'></td>
                                </tr>
                                <tr>
                                    <th>Next Playlist: </th>
                                    <td id='nextPlaylist'></td>
                                </tr>
                            </table>
                        </div>
                        <div class='statusBoxRight'>
                            <table class='statusTable'>
                                <tr>
                                    <th class='schedulerStartTime'>Started at:</th>
                                    <td class='schedulerStartTime' id='schedulerStartTime'></td>
                                </tr>
                                <tr>
                                    <th class='schedulerEndTime'><span id='schedulerStopType'></span> Stop at:</th>
                                    <td class='schedulerEndTime' id='schedulerEndTime'></td>
                                </tr>
                                <tr>
                                    <td class='schedulerEndTime schedulerExtend' colspan='2'>
                                        <input type='button' class="btn btn-primary btn-sm" value='Extend' onClick='ExtendSchedulePopup();'>
                                        <input type='button' class="btn btn-primary btn-sm" value='+5m' onClick='ExtendSchedule(5);'>
                                    </td>
                                </tr>
                            </table>
                        </div>
                        <div class="clear"></div>
                        <hr>
                    </div>

                    <div id="playerStatusTop">
                        <div class='statusBoxLeft'>
                            <table class='statusTable'>
                                <tr>
                                    <th>Player Status:</th>
                                    <td id="txtPlayerStatus" style="text-align:left; width=80%"></td>
                                </tr>
                                <tr>
                                    <th>Playlist:</th>
                                    <td><select id="playlistSelect" name="playlistSelect" size="1" onClick="SelectPlaylistDetailsEntryRow();PopulatePlaylistDetailsEntries(true,'');" onChange="PopulatePlaylistDetailsEntries(true,'');"></select>
                                        &nbsp;&nbsp;&nbsp;
                                        <b>Repeat:</b> <input type="checkbox" id="chkRepeat"></input>
                                    </td>
                                </tr>
                                <tr>
                                    <th>Volume [<span id='volume' class='volume'></span>]:</th>
                                    <td>
                                        <input type="button" class='volumeButton btn btn-primary btn-sm' value="-" onClick="DecrementVolume();">
                                        <span id="slider"></span> <!-- the Slider -->
                                        <input type="button" class='volumeButton btn btn-primary btn-sm' value="+" onClick="IncrementVolume();">
                                        <span id='speaker'></span> <!-- Volume -->
                                    </td>
                                </tr>
                                <tr>
                                    <th>Playlist Details:</th>
                                </tr>
                            </table>
                            <table>
                                <tr>
                                    <td>
                                        <? PrintSetting('verbosePlaylistItemDetails', 'VerbosePlaylistItemDetailsToggled'); ?>
                                    </td>
                                </tr>
                            </table>
                        </div>
                        <div class='statusBoxRight'>
                            <table id='playerTime' class='statusTable'>
                                <tr>
                                    <th>Elapsed:</th>
                                    <td id="txtTimePlayed"></td>
                                </tr>
                                <tr>
                                    <th>Remaining:</th>
                                    <td id="txtTimeRemaining"></td>
                                </tr>
                                <tr>
                                    <th>Randomize:</th>
                                    <td id="txtRandomize"></td>
                                </tr>
                            </table>
                        </div>
                        <div class="clear"></div>
                    </div>

                    <div id="playerStatusBottom">
                        <?
include "playlistDetails.php";
?>
                        <center>
                            <div id="playerControls" class="btn-group" role="group">
                                <button id="btnPlay" type="button" class="btn btn-primary" onClick="StartPlaylistNow();">Play</button>
                                <button id="btnPrev" type="button" class="btn btn-primary" onClick="PreviousPlaylistEntry();">Previous</button>
                                <button id="btnNext" type="button" class="btn btn-primary" onClick="NextPlaylistEntry();">Next</button>
                                <div class="btn-group" role="group">
                                    <button id="btnGroupDrop1" type="button" class="btn btn-primary dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                                        Stop
                                    </button>
                                    <div class="dropdown-menu" aria-labelledby="btnGroupDrop1">
                                        <a id="btnStopGracefully" type="button" class="dropdown-item" value="" onClick="StopGracefully();">Stop Gracefully</a>
                                        <a id="btnStopGracefullyAfterLoop" type="button" class="dropdown-item" value="" onClick="StopGracefullyAfterLoop();">Stop After Loop</a>
                                        <a id="btnStopNow" type="button" class="dropdown-item " value="" onClick="StopNow();">Stop Now</a>
                                    </div>
                                </div>
                            </div>
                        </center>
                        <div id='deprecationWarning' style='display:none'>
                            <font color='red'><b>* - Playlist items marked with an asterisk have been deprecated and will be auto-upgraded the next time you edit the playlist.</b></font>
                        </div>
                    </div>
                </div>

            </div>
            <?php include 'common/footer.inc'; ?>
        </div>
        <div id='upgradePopup' title='FPP Upgrade' style="display: none">
            <textarea style='width: 99%; height: 97%;' disabled id='upgradeText'>
    </textarea>
            <input id='rebootFPPAfterUpgradeButton' type='button' class='buttons' value='Reboot' onClick='Reboot();' style='display: none;'>

        </div>
</body>

</html>