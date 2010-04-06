﻿/**
 * Copyright 2008 - TMTDigital LLC
 *
 * Author:   Travis Tidwell (www.travistidwell.com)
 * Version:  1.0
 * Date:     June 9th, 2008
 **/
import fl.transitions.*;
import fl.transitions.easing.*;
import flash.geom.Rectangle;

var dashBase:*;
var dashService:*; 
var dashResizer:*;
var dashUtils:*;
var dashLayout:*;
var flashVars:*;
var dashInterface:*;

var mediaRect:Rectangle;

var menuTween:Tween;
var controlTween:Tween;
		
var node:MovieClip = dash.node;
var values:MovieClip = dash.node.fields.values;
var media:MovieClip = dash.node.fields.media;
var controlBar:MovieClip = dash.node.fields.media.controlBar;
var minMaxNode:MovieClip = dash.node.fields.media.controlBar.minMaxNode;
var menuButton:MovieClip = dash.node.fields.media.controlBar.menuButton;
var toggleFullScreen:MovieClip = dash.node.fields.media.controlBar.toggleFullScreen;
var logo:MovieClip = dash.node.fields.logo;
var playlist:MovieClip = dash.playlist;

var menuVisible:Boolean = false;
var barWidth:Number = playlist.navigation.bar.width;

/**
 * The skin.as file can be used by your skin to hook into the Dash Media Player and 
 * completely customize how the player behaves.  It allows you to use many of the facilities already
 * placed in the Dash Media Player so that you can truely have your very own player using the power
 * of the Dash Media Player.  For more information, please go to <a href="http://www.tmtdigital.com/node/140">http://www.tmtdigital.com/node/140</a>
 **/
//class SkinningAPI {}	
		
/**
 * Function to initialize your skin.  
 *
 * @param dashBase - The Dash Media Player Base class.
 * @param dashService - The Dash Media Player Service class. (for calling services to Drupal and others).
 * @param dashResizer - The Dash Media Player Resizer class (for resizing objects)
 * @param dashUtils - The Dash Media Player Utils class. (common utilities used throughout the player).
 * @param dashLayout - The Dash Media Player Layout Manager. (to store all information from the layout XML file)
 * @param flashVars - The Flash Variables Object (for handling all flashvars).
 * @param dashInterface - The Dash Media Player Interface class (for loading nodes, playlists, and handling media).
 *
 * @return True to indicate to the media player to start loading content.
 *         False to let the skin take over from here and do what it needs to do.
 */

function initialize( _dashBase:*, _dashService:*, _dashResizer:*, _dashUtils:*, _dashLayout:*, _flashVars:*, _dashInterface:* ) : Boolean
{
   dashBase = _dashBase;
   dashService = _dashService;
   dashResizer = _dashResizer;
   dashUtils = _dashUtils;
   dashLayout = _dashLayout;
   flashVars = _flashVars;
   dashInterface = _dashInterface;
   
   // We want to keep track of our media region size during dynamic resizing... this is how.
   mediaRect = new Rectangle( media.mediaRegion.x, media.mediaRegion.y, media.mediaRegion.width, media.mediaRegion.height );
   dashResizer.addResizeProperty( mediaRect, "dash/node/fields/media/mediaRect", "width" ); 
   dashResizer.addResizeProperty( mediaRect, "dash/node/fields/media/mediaRect", "height" );

   setPlaylistSize( flashVars.playlistsize );
   showPlaylistLinks();
	
   dash.node.fields.menu.visible = false;
   return true;
}

/**
 * Allows you to provide all your information within your skin file so that you do not have to expose the configuration XML
 * file to outside parties.  You can also associate certain FlashVariables with your skin by using the "flashvars" section of
 * the XML configuration. Each of these tags are described as follows.  For more information, go to <a href="http://www.tmtdigital.com/node/143">http://www.tmtdigital.com/node/143</a>
<table>
 <thead><tr><th>Element</th><th>Description</th> </tr></thead>
 <tbody>
 <tr class="odd"><td><strong>license</strong></td><td>This is where you will place your license if you purchase a license for commercial use.</td> </tr>
 <tr class="even"><td><strong>gateway</strong></td><td>This is the URL to your Drupal Services Gateway.</td> </tr>

 <tr class="odd"><td><strong>apiKey</strong></td><td>This is the Services API Key to provide a secure connection between the player and your Drupal site</td> </tr>
 <tr class="even"><td><strong>baseURL</strong></td><td>This is the Base URL of your domain name.  For this site, this value is <strong>http://www.tmtdigital.com</strong></td> </tr>
 <tr class="odd"><td><strong>flashvars</strong></td><td>Allows you to pre-define flash variables so that they are not required when you embed the player in your page.  For example, if you wish to have all your players autostart the media, then you can provide a <strong>&lt;autostart&gt;true&lt;/autostart&gt;</strong> tag within this flashvars tag.</td> </tr>
</tbody>
</table>
 *
 * @return Your XML configuration, as it would be in the dashconfig.xml file.
 */
 
function getConfigInfo() : XML
{
   var settings:XML = 
            <params>
               <license></license>
               <gateway></gateway>
               <apiKey></apiKey>
               <baseURL></baseURL>
               <flashvars>
						<autoscroll>true</autoscroll>
						<vertical>true</vertical>
						<volumevertical>false</volumevertical>
						<linksvertical>false</linksvertical>
						<seekvertical>false</seekvertical>
						<teaserplay>false</teaserplay>
               </flashvars>
            </params>;
   
   return settings;
}

/**
 * Returns the layout information of this skin as an XML structure.  This is used to define the resize properties used for each
 * element within the skin.  Each element within the XML structure is defined as follows.  For more information, go to 
 * <a href="http://www.tmtdigital.com/node/140">http://www.tmtdigital.com/node/140</a>.

<table>
 <thead><tr><th>Element</th><th>Description</th> </tr></thead>
 <tbody>
 <tr class="odd"><td><strong>width</strong></td><td>This is the original with of your skin (before it gets resized)</td> </tr>
 <tr class="even"><td><strong>height</strong></td><td>This is the original height of your skin (before it gets resized)</td> </tr>

 <tr class="odd"><td><strong>autohideX</strong></td><td>This is the minimum width that your skin can be before the playlist is hidden automatically.</td> </tr>
 <tr class="even"><td><strong>autohideY</strong></td><td>This is the minimum height that your skin can be before the information box is hidden automatically.</td> </tr>
 <tr class="odd"><td><strong>spacer</strong></td><td>This is the space between the Playlist and your Main Node.</td> </tr>
 <tr class="even"><td><strong>linkpadding</strong></td><td>This is the space on either side of the text within a playlist link to be used as padding.</td> </tr>

 <tr class="odd"><td><strong>resize</strong></td><td>There can be an unlimited number of these tags in your layout.  Basically what this tag indicates is a resizable object property when your skin is resized.  If you wish to have an object in your skin float right with a resize of the player, then you would provide the path to that object and then the <strong>x</strong> property as the value that will move with the size of the player.  If you wish for that object to float right and also float to the bottom during a resize event, then you will need to provide two different resize tags where one provides the <strong>x</strong> property, and the other provides the <strong>y</strong> property of your object.  You can also set the "width" and "height" properties if you wish for the object to resize with the player.</td> </tr>
</tbody>
</table>
 *
 * @return The XML layout information.
 */

function getLayoutInfo() : XML
{
   var layout:XML = 
   <layout>
   	<width>651</width>
   	<height>426</height>
   	<autoHideX>455</autoHideX>
   	<autoHideY>340</autoHideY>	
   	<spacer>1</spacer>
   	<linkpadding>10</linkpadding>		
   	<resize>
   		<path>dash/node/loader/loader_back</path>
   		<property>width</property>
   		<property>height</property>
   	</resize>	   
   	<resize>
   		<path>dash/node/loader/loader_mc</path>
   		<property>x</property>
   		<property>y</property>
   	</resize>
   	<resize>
   		<path>dash/node/fields/values/backgroundMC</path>
   		<property>width</property>
   	</resize>
   	<resize>
   		<path>dash/node/fields/values</path>
   		<property>y</property>
   	</resize>								
      <resize>
         <path>dash/node/fields/taxonomy</path>
         <property>x</property>
         <property>y</property>      
      </resize>
   	<resize>
   		<path>dash/node/fields/media/mediaRegion</path>
   		<property>width</property>
   		<property>height</property>
   	</resize>
   	<resize>
   		<path>dash/node/fields/media/spectrum</path>
   		<property>width</property>
   		<property>height</property>
   	</resize>		
   	<resize>
   		<path>dash/node/fields/media/controlBar</path>
   		<property>y</property>
   	</resize>
   	<resize>
   		<path>dash/node/fields/media/controlBar/invalid</path>
   		<property>width</property>
   	</resize>				
   	<resize>
   		<path>dash/node/fields/media/controlBar/seekBar/control/button/seekWidth</path>
   		<property>width</property>
   	</resize>													
   	<resize>
   		<path>dash/node/fields/media/controlBar/seekBar/backgroundMC/backgroundGrad</path>
   		<property>width</property>
   	</resize>				
   	<resize>
   		<path>dash/node/fields/media/controlBar/seekBar/backgroundMC/background</path>
   		<property>width</property>
   	</resize>
   	<resize>
   		<path>dash/node/fields/media/controlBar/seekBar/totalTime</path>
   		<property>x</property>
   	</resize>
   	<resize>
   		<path>dash/node/fields/media/controlBar/volumeBar</path>
         <property>x</property>
   	</resize>  
   	<resize>
   		<path>dash/node/fields/media/controlBar/minMaxNode</path>
         <property>x</property>
   	</resize>  
   	<resize>
   		<path>dash/node/fields/media/controlBar/toggleFullScreen</path>
         <property>x</property>
   	</resize>  
   	<resize>
   		<path>dash/node/fields/media/controlBar/menuButton</path>
         <property>x</property>
   	</resize>
   	<resize>
   		<path>dash/node/fields/menu/backgroundMC</path>
   		<property>width</property>
   		<property>height</property>
   	</resize>
   	<resize>
   		<path>dash/node/fields/menu/embed</path>
   		<property>y</property>
   	</resize>
   	<resize>
   		<path>dash/node/fields/menu/embed/embedcode</path>
   		<property>width</property>
   	</resize>			
   	<resize>
   		<path>dash/node/fields/views</path>
   		<property>x</property>
   		<property>y</property>
   	</resize>	   
   	<resize>
   		<path>dash/node/fields/voter</path>
   		<property>x</property>
   		<property>y</property>
   	</resize>	   
   	<resize>
   		<path>dash/playlist</path>
   		<property>x</property>
   	</resize>
   	<resize>
   		<path>dash/playlist/backgroundMC</path>
   		<property>height</property>
   	</resize>								
   	<resize>
   		<path>dash/playlist/scrollRegion/listMask</path>
   		<property>height</property>
   	</resize>
   	<resize>
   		<path>dash/playlist/loader/loader_back</path>
   		<property>height</property>
   	</resize>
   	<resize>
   		<path>dash/playlist/loader/loader_mc</path>
   		<property>y</property>
   	</resize>	   
   	<resize>
   		<path>dash/playlist/autoNext</path>
   		<property>y</property>
   	</resize>		   
   	<resize>
   		<path>dash/playlist/navigation</path>
   		<property>y</property>
   	</resize>	   
   </layout>;
      
   return layout;
}


/**
 * This function is a hook which can be used to control each and every service call that is made from within 
 * the player.  Before the player makes any calls to the server, it will first pass the message that will be
 * sent to this function to allow the skin to modify the message being sent to the player.  This will allow
 * the skin to make any changes necessary to the message (such as changing the service command), as well as
 * add any arguments to the message.
 *
 * @param message - The message object.  Each message object contains the following...<br/>
 * <em>command</em> - This is a command that is getting sent to the skin.  The following is a list of all commands...
 * <ul>
 * <li><em>System.SYSTEM_CONNECT</em> - Called when the player connects to Drupal.</li>
 * <li><em>System.SYSTEM_MAIL</em> - Called when an email message is sent from the player.</li>
 * <li><em>System.NODE_LOAD</em> -Called when the player makes a call to load a node.</li>
 * <li><em>System.GET_VERSION</em> - Called when the player queries Drupal for the version #</li>
 * <li><em>System.GET_VIEW</em> - Called when the player queries for the Drupal view (playlist)</li>
 * <li><em>System.GET_VOTE</em> - Called when the player queries to get a vote.</li>
 * <li><em>System.SET_VOTE</em> - Called when the player queries to set a vote.</li>
 * <li><em>System.GET_USER_VOTE</em> - Called when the player queries to get a user vote.</li>
 * <li><em>System.DELETE_VOTE</em> - Called when the player deletes a vote.</li>
 * <li><em>System.ADD_TAG</em> - Called when the player adds a new taxonomy tag to a node.</li>
 * <li><em>System.INCREMENT_NODE_COUNTER</em> - Called when the player increments the node counter.</li>
 * <li><em>System.SET_FAVORITE</em> - Called when the player sets a new favorite node.</li>
 * <li><em>System.DELETE_FAVORITE</em> - Called when the player deletes a favorite.</li>
 * <li><em>System.IS_FAVORITE</em> - Called when the player queries to see if this node is a favorite.</li>
 * <li><em>System.USER_LOGIN</em> - Called when the player logs the user into the Drupal system.</li>
 * <li><em>System.USER_LOGOUT</em> - Called when the player logs the user out.</li>
 * <li><em>System.SET_USER_STATUS</em> - Called when the player sets the user status.</li>
 * </ul>
 * <em>onSuccess</em> - The callback that is called when a successful call has been made.<br/>
 * <em>onFailed</em> - The callback that is called when an error occurs.<br/>
 * <em>args</em> - An array of all the arguments for this view.<br/>
 *
 * @return You can use the return of this function to tell the player to make the call or not.
 *           If you do not want the player to make any call to the server, then you would simply 
 *           provide false for the return value, true otherwise.
 */
function serviceCall( message:Object ) : Boolean
{
	return true;
}

/**
 * Hook that gets called when the player resizes.
 */
function onResize() : void
{
}

/**
 * When your media type is "custom", the dash media player will then call this routine to grab a media handling
 * class.  This can be anything class to handle any type of media like SWF files, ect.  
 * For an example stub class to be used to build your own, refer to the SWFMedia.as file.
 *
 * @param mediaFile - The media file object to play.  This object contains the following...<br/>
 *             <ul>
 *             <li><em>path</em> - The full path of the media file.</li>
 *             <li><em>filename</em> - The filename of the media file.</li>
 *             <li><em>extension</em> - The file extension...</li>
 *             <li><em>mediatype</em> - The media type...</li>
 *             <li><em>mediaclass</em> - This will always be "media" here...</li>
 *             <li><em>weight</em> - The weight of this media.</li>
 *             </ul>
 *
 * @return Your custom media class           
 */

function getMedia( mediaFile:Object )
{
   // This is just an example...  not working yet, but if anyone is up for the challenge... ;)
   if( mediaFile.mediatype == "custom" ) 
   {
      /**
       * Example on how this is done... the SWFMedia is only a stub file right now, but maybe someone can
       * get it working.  ;)
       *
       *    var mediaHandler:SWFMedia = new SWFMedia();
       *    media.mediaRegion.addChild( mediaHandler );
       *    return mediaHandler;
       */
      
      return null;
   }
   else 
   {
      return null;
   }
}

/**
 * Called when the media starts playing...
 */
function onMediaPlaying()
{
}

/**
 * Called when the media finishes playing...
 */
function onMediaComplete()
{
}

/**
 * Hook that allows you to return a MovieClip of your teaser.
 *
 * @return A new movie clip of your teaser.
 */
function getTeaser() : MovieClip
{
   return new mcTeaser();
}

/**
 * Called when the teaser gets initialized.
 *
 * @param teaser - The teaser object.
 */
function onTeaserInit( teaser:* )
{
	if( teaser.skin.backgroundMC )
	{
	   teaser.skin.backgroundMC["selected"].gotoAndStop( "_on" );
	   teaser.skin.backgroundMC["normal"].gotoAndStop( "_on" );			
   }
}

/**
 * Called when the teaser gets selected.
 *
 * @param teaser - The teaser object.
 * @param select - If the teaser has been selected or not
 */
function onTeaserSelect( teaser:*, select:Boolean ) 
{
	if( teaser.skin.backgroundMC )
   {
		teaser.skin.backgroundMC["selected"].visible = select;
      teaser.skin.backgroundMC["normal"].visible = !select;
	}
}

/**
 * Called when the mouse hovers over a teaser
 *
 * @param teaser - The teaser object.
 */
function onTeaserOver( teaser:* )
{
	if( teaser.skin.backgroundMC )
   {		
	   teaser.skin.backgroundMC["selected"].gotoAndStop( "_over" );
	   teaser.skin.backgroundMC["normal"].gotoAndStop( "_over" );
	}	
}

/**
 * Called when the mouse moves out of hovering over a teaser.
 *
 * @param teaser - The teaser object.
 */
function onTeaserOut( teaser:* )
{
	if( teaser.skin.backgroundMC )
   {		
	   teaser.skin.backgroundMC["selected"].gotoAndStop( "_on" );
	   teaser.skin.backgroundMC["normal"].gotoAndStop( "_on" );
	}	
}

/**
 * Called when the user presses the down button on the teaser.
 *
 * @param teaser - The teaser object.
 */
function onTeaserDown( teaser:* )
{
	if( teaser.skin.backgroundMC )
   {		
	   teaser.skin.backgroundMC["selected"].gotoAndStop( "_down" );
	   teaser.skin.backgroundMC["normal"].gotoAndStop( "_down" );
	}
}

/**
 * Hook that allows you to return a MovieClip of a playlist link.
 *
 * @return A new movie clip of your playlist link.
 */
function getPlaylistLink() : MovieClip
{
   return new mcPlaylistLink();
}

/**
 * Hook that allows you to return a MovieClip of a term link.
 *
 * @return A new movie clip of your term link.
 */
function getTermLink() : MovieClip
{
   return new mcTermLink();
}

/**
 * Hook that gets called when a node loads in the system
 *
 * @param node - A standard Drupal node object.
 */
function onNodeLoad( node:Object )
{
}

/**
 * Hook that gets called when a node loads in the system
 *
 * @param playlist - A standard Drupal view object.
 */
function onPlaylistLoad( playlist:Object )
{
}

/**
 * Hook when the mouse is moved when the player is in full screen mode.
 *
 * @param mouseX - The x-position of the mouse.
 * @param mouseY - The y-position of the mouse.
 */
function onFullScreenMove( mouseX:Number, mouseY:Number )
{
   if( (flashVars.vertical && (mouseX > 0.75*dashBase.stageWidth)) ||
       (!flashVars.vertical && (mouseY > 0.75*dashBase.stageHeight)) ) 
   {
		dashBase.setMaximize( flashVars.disableplaylist, true );		
   }

   if( controlTween ) {			
      controlTween.stop();
   }
   
   controlBar.alpha = 1;
	controlBar.seekBar.totalTime.visible = true;
	controlBar.seekBar.playTime.visible = true;		
}

/**
 * Hook when the inactive timout occurs when in full screen mode.  Typically you should
 * hide everything at this point.
 */
function onFullScreenHide()
{
   dashBase.setMaximize( true, true );
   controlTween = new Tween( controlBar, "alpha", Strong.easeIn, controlBar.alpha, 0, 20 );
	controlBar.seekBar.totalTime.visible = false;
	controlBar.seekBar.playTime.visible = false;	
}

/**
 * Hook when the player goes in and out of full screen.
 *
 * @param full - To determine if we are in fullscreen mode or not...<br/>
 *               <em>true</em> - Fullscreen<br/>
 *               <em>false</em> - Normal
 */
function onFullScreen( full:Boolean ) 
{
   toggleFullScreen.onButton.visible = full;
	toggleFullScreen.onButton.buttonMode = full;
   toggleFullScreen.onButton.mouseChildren = !full;
   toggleFullScreen.offButton.visible = !full;
	toggleFullScreen.offButton.buttonMode = !full;
   toggleFullScreen.offButton.mouseChildren = full;
	node.fields.voter.visible = !full && flashVars.votingenabled && flashVars.showinfo;
   
   if( full ) {
      var newMediaRect:Rectangle = new Rectangle( 0, 0, dashBase.stageWidth, dashBase.stageHeight );
   		
      if( playlist && !dashBase.maximized ) {
         newMediaRect.width -= (playlist.scrollRegion.listMask.width);
      }		
      else {
         newMediaRect.width += 2*dashLayout.spacer;
      }			

      dashResizer.setRect( media.mediaRegion, "dash/node/fields/media/mediaRegion", newMediaRect );
      dashResizer.setRect( node.loader, "dash/node/loader", newMediaRect );

      onFullScreenHide(); 
   }
   else {
      dashResizer.setRect( media.mediaRegion, "dash/node/fields/media/mediaRegion", mediaRect );
      dashResizer.setRect( node.loader, "dash/node/loader", mediaRect ); 
      
      if( controlTween ) {			
         controlTween.stop();
      }
      
      controlBar.alpha = 1; 
		controlBar.seekBar.totalTime.visible = true;
		controlBar.seekBar.playTime.visible = true;				
   }		
}

/**
 * Ability to change how the resizer tweens its resize transitions.
 */
function getTweenFunction() : Function
{
   return Strong.easeIn;
}

/**
 * Called when the toggle menu mode button gets pressed.
 *
 * @param on - Boolean to let us know if the Menu should be on or off...<br/>
 *             <em>true</em> - menu is on.<br/>
 *             <em>false</em> - menu is off.<br/>
 * @param tween - Let us know if this movement should be tweened or not.
 */
function toggleMenuMode( on:Boolean, tween:Boolean )
{
	menuVisible = on;
	
	if( menuVisible ) {
	   dash.node.fields.menu.visible = menuVisible;
	}
	
	var newX:Number = on ? 0 : -(dash.node.fields.menu.width + 5);
	if( menuTween ) {
		menuTween.stop();
	}		

	menuTween = new Tween( dash.node.fields.menu, "x", Strong.easeIn, dash.node.fields.menu.x, newX, 15 );
	menuTween.removeEventListener( TweenEvent.MOTION_FINISH, onMenuFinish );
	menuTween.addEventListener( TweenEvent.MOTION_FINISH, onMenuFinish );	
}

/**
 * Called when the menu has finished moving off the screen.  Here we will just hide the menu when 
 * it is not in use.
 *
 * @param event - A standard tween event.
 */

function onMenuFinish(event:TweenEvent) 
{
	dash.node.fields.menu.visible = menuVisible;
}

/**
 * Called to hide or show the Min/Max button.
 *
 * @param show - Determine if we should show or hide the minMaxButton.<br/>
 *               <em>true</em> - Show the min/max button.<br/>
 *               <em>false</em> - Hide the min/max button.
 */
function showMinMaxButton( show:Boolean )
{
   minMaxNode.visible = show;
   var xOffset:Number = (minMaxNode.width + dashLayout.spacer);
   xOffset *= show ? 1 : -1;
   minMaxNode.x += xOffset;
   dashResizer.setResizeProperty( menuButton, "dash/node/fields/media/controlBar/menuButton", "x", ( menuButton.x + xOffset ) );
   dashResizer.setResizeProperty( toggleFullScreen, "dash/node/fields/media/controlBar/toggleFullScreen", "x", ( toggleFullScreen.x + xOffset ) );
   dashResizer.resizeObject( controlBar, "dash/node/fields/media/controlBar", (controlBar.width - xOffset), controlBar.height, false, false );
} 

/**
 * Called to hide or show the Menu button.
 *
 * @param show - Determine if we should hide or show the menuButton.<br/>
 *               <em>true</em> - Show the menu button.<br/>
 *               <em>false</em> - Hide the menu button.
 */
function showMenuButton( show:Boolean )
{
   menuButton.visible = show;		
   var xOffset:Number = (menuButton.width + dashLayout.spacer);
   xOffset *= show ? 1 : -1;
   dashResizer.setResizeProperty( menuButton, "dash/node/fields/media/controlBar/menuButton", "x", ( menuButton.x + xOffset ) );
   dashResizer.resizeObject( controlBar, "dash/node/fields/media/controlBar", (controlBar.width - xOffset), controlBar.height, false, false );
}

/**
 * Called to hide or show the media player information section.
 *
 * @param show - Determine if we should hide or show the Info section.
 *               <em>true</em> - Show the information.<br/>
 *               <em>false</em> - Hide the information.
 * @param tween - Boolean to indicate if this transition should be tweened or not.
 * @param refresh - Boolean to indicate if there should be a full screen refresh after the transition.
 */
function showInfo( show:Boolean, tween:Boolean, refresh:Boolean )
{
   var newHeight:Number = (values.y - media.mediaRegion.y - dashLayout.spacer);
	node.fields.voter.visible = show && flashVars.votingenabled;	
	newHeight += show ? 0 : values.height;
	dashResizer.resizeObject( media.mediaRegion, "dash/node/fields/media/mediaRegion", media.mediaRegion.width, newHeight, false, false );
	dashResizer.resizeObject( mediaRect, "dash/node/fields/media/mediaRect", media.mediaRegion.width, newHeight, false, false );
	dashResizer.resizeObject( dash.node.fields.menu, "dash/node/fields/menu", dash.node.fields.menu.width, newHeight, false, refresh );	
}

/**
 * Called to hide or show the media player controls.
 *
 * @param show - Determine if we should hide or show the controls.
 *               <em>true</em> - Show the controls.<br/>
 *               <em>false</em> - Hide the controls.<br/>
 * @param tween - Boolean to indicate if this transition should be tweened or not.
 */
function showControls( show:Boolean, tween:Boolean ) 
{
   var yOffset:Number = controlBar.height + dashLayout.spacer;
   yOffset *= show ? -1 : 1;
   dashResizer.resizeObject( node, "dash/node", node.width, node.height + yOffset, tween );
}

/**
 * Called to maximize/minimize the player (show or hide the playlist).
 *
 * @param max - Boolean to determine if we should maximize the player or not.
 *              <em>true</em> - Maximize (hide the playlist).
 *              <em>false</em> - Minimize (show the playlist).
 * @param tween - Boolean to indicate if this transition should be tweened or not.
 */
function maximize( max:Boolean, tween:Boolean = true )
{
   if( dashBase.maximized != max )
   {
      dashBase.maximized = max;
      var xOffset:Number = 0;
      var yOffset:Number = 0;
      			
      if( flashVars.vertical ) {
	      xOffset = playlist.scrollRegion.listMask.width + 2*dashLayout.spacer;
      }
      else {
	      yOffset = playlist.height + 2*dashLayout.spacer;
      }
      			
      xOffset *= (max) ? 1 : -1;		
      yOffset *= (max) ? 1 : -1;			
      dashResizer.resizeLayout( "dash", xOffset, yOffset, tween );
   }
}

/**
 * Allow the skin to provide their own embed code.
 *
 *	@param loaderURL - The URL of the player SWF file.
 * @param mediaFile - The path to the media file to embed.
 * @param imageFile - The image provided with the media file to embed.
 * @param embedVars - An array of extra flashVars.
 */
function getEmbedCode( loaderURL:String, mediaFile:String, imageFile:String, embedVars:Array )
{
	var paramVars:String = ((embedVars.length > 0) ? embedVars.join("&") : "");
	var flashVarString:String = "";
	
	if( mediaFile )
	{
		flashVarString = "file=" + mediaFile;
		flashVarString += "&autostart=false";
							
		if( imageFile ) {
			flashVarString += "&image=" + imageFile;
		}
						
		flashVarString += paramVars ? ("&" + paramVars) : "";			
	}
	
	var embedText:String = "<object classid=\"clsid:D27CDB6E-AE6D-11cf-96B8-444553540000\" ";
	embedText += "width=\""  + flashVars.embedwidth  + "\" ";
	embedText += "height=\"" + flashVars.embedheight + "\" ";
	embedText += "codebase=\"http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab\">\n";
	embedText += "<param name=\"movie\" value=\"" + loaderURL + "\" />\n";
	embedText += "<param name=\"wmode\" value=\"transparent\" />\n";
	embedText += "<param name=\"allowfullscreen\" value=\"true\" />\n";
	embedText += "<param name=\"FlashVars\" value=\"" + flashVarString + "\" />\n";
	embedText += "<param name=\"quality\" value=\"high\" />\n";
	embedText += "<embed allowScriptAccess=\"always\" src=\"" + loaderURL + "\" ";
	embedText += "width=\""  + flashVars.embedwidth  + "\" ";
	embedText += "height=\"" + flashVars.embedheight + "\" ";
	embedText += "border=\"0\" type=\"application/x-shockwave-flash\" ";
	embedText += "pluginspage=\"http://www.macromedia.com/go/getflashplayer\" wmode=\"transparent\" ";
	embedText += "allowfullscreen=\"true\" quality=\"high\" ";
	embedText += "flashvars=\"" + flashVarString + "\" />\n</object>\n";	
	return embedText;
}

/**
 * Called to set the width or height of the playlist.
 *
 * @param playlistSize - The size (in pixels) that you would like to set the playlist.
 */
function setPlaylistSize( playlistSize:Number )
{
   if( playlistSize )
   {
      var _x:String = (flashVars.vertical) ? "x" : "y";
      var _width:String = (flashVars.vertical) ? "width" : "height";
      
      var offset:Number = playlistSize - playlist.scrollRegion.listMask[_width];
      dashResizer.setResizeProperty( playlist, "dash/playlist", _x, (playlist[_x] - offset) );
   	
	   if( playlist.backgroundMC ) {
		   playlist.backgroundMC[_width] += offset;
	   }
      
	   playlist.scrollRegion.listMask[_width] = playlistSize; 
	   playlist.loader["loader_back"][_width] = playlistSize;
      playlist.loader["loader_mc"][_x] = (playlistSize - playlist.loader["loader_mc"][_width]) / 2;
   	
	   if( flashVars.vertical ) {
		   if( playlist.links ) {
			   playlist.links.listMask.width += offset;
		   }
   		
		   if( playlist.autoPrev ) {
			   playlist.autoPrev.width += offset;
		   }
   		
		   if( playlist.autoNext ) {
			   playlist.autoNext.width += offset;
		   }
   		
		   if( playlist.navigation ) {
		      playlist.navigation.next.x += offset;
   		   
		      if( playlist.navigation.bar ) {
		         playlist.navigation.bar.width += offset;
		         playlist.navigation.grad.width += offset;
		         barWidth = playlist.navigation.bar.width;
		      }
		   }
	   }
   	
	   var nodeWidth = (flashVars.vertical) ? (node.width - offset) : node.width;
	   var nodeHeight = (flashVars.vertical) ? node.height : (node.height - offset);				
	   dashResizer.resizeObject( node, "dash/node", nodeWidth, nodeHeight );
	}
}

/**
 * Hook to allow your to format the time indication however you would like it to be formated.
 *
 *	@param mediaTime - The time in seconds.
 * 
 * @return An object that represents both the units and the time as Strings.
 */
function formatTime(mediaTime:Number) : Object
{
	var seconds:Number = 0;
	var minutes:Number = 0;
	var hour:Number = 0;
	
	hour = Math.floor(mediaTime / 3600);
	mediaTime -= (hour * 3600);
	minutes = Math.floor( mediaTime / 60 );
	mediaTime -= (minutes * 60);
	seconds = Math.floor(mediaTime % 60);

	var timeString:String = "";
	
	if( hour ) {
		timeString += String(hour);
		timeString += ":";
	}
	
	timeString += (minutes >= 10) ? String(minutes) : ("0" + String(minutes));
	timeString += ":";
	timeString += (seconds >= 10) ? String(seconds) : ("0" + String(seconds));
	return {time:timeString, units:""};
}

/**
 * Called to show the dynamic links for the playlist.
 */
function showPlaylistLinks()
{
	if( (flashVars.linktext[0]) && (playlist.links.y == playlist.y) ) 
   {
	   var yOffset:Number = playlist.links.height;
   	
	   if( !flashVars.vertical && playlist.navigation ) {
		   playlist.navigation.height -= yOffset;
		   playlist.navigation.y += yOffset;
	   }
		
	   if( flashVars.vertical && playlist.autoPrev ) {
		   playlist.autoPrev.y += yOffset;					
	   }
		
		if( playlist.scrollRegion ) {
	   	dashResizer.setResizeProperty( playlist.scrollRegion.listMask, "dash/playlist/scrollRegion/listMask", "height", (playlist.scrollRegion.listMask.height - yOffset) );
	   	playlist.scrollRegion.y += yOffset;
		}
		
		if( playlist.loader ) {
			dashResizer.setResizeProperty( playlist.loader["loader_back"], "dash/playlist/loader/loader_back", "height", (playlist.loader["loader_back"].height - yOffset) );
			dashResizer.setResizeProperty( playlist.loader["loader_mc"], "dash/playlist/loader/loader_mc", "y", (playlist.loader["loader_mc"].y - yOffset) );			
			playlist.loader.y += yOffset;
		}
		
		if( playlist.backgroundMC ) {
			dashResizer.setResizeProperty( playlist.backgroundMC, "dash/playlist/backgroundMC", "height", (playlist.backgroundMC.height - yOffset) );
			playlist.backgroundMC.y += yOffset;
		}
   }
}

/**
 *  Automatically places the previous and next buttons depending of whether there is a previous or next playlist.
 *
 *  @param nextVisible - A boolean to indicate if there should be a next button for the playlist.
 *  @param prevVisible - A boolean to indicate if there should be a previous button for the playlist.
 */
function setNavBar( nextVisible:Boolean, prevVisible:Boolean ) 
{
   if( barWidth && playlist.navigation.bar && playlist.navigation.next && playlist.navigation.prev )
	{
	   var newWidth:Number = barWidth;
		newWidth += nextVisible ? 0 : playlist.navigation.next.width + dashLayout.spacer;
		newWidth += prevVisible ? 0 : playlist.navigation.prev.width + dashLayout.spacer;
		playlist.navigation.bar.width = playlist.navigation.grad.width = newWidth;			
		playlist.navigation.bar.x = playlist.navigation.grad.x = prevVisible ? (playlist.navigation.prev.x + playlist.navigation.prev.width + dashLayout.spacer) : playlist.navigation.prev.x;			
		playlist.navigation.prev.visible = prevVisible;
		playlist.navigation.next.visible = nextVisible;
   }
}

/**
 *  Allows you to set the logo position.  You must have a valid license for this function to get called...
 *
 *  @param addObject - A boolean that will indicate if the logo needs to be added as a dynamic property to the resizer.
 */
function setLogoPos( addObject:Boolean )
{
   var logoPath:String = "dash/node/fields/logo";
   var obj:* = dashUtils.getObjectFromPath( dash, logoPath ); 

   switch( flashVars.logopos.toLowerCase() )
   {
      case "bl":
	      if( addObject ) {
		      dashResizer.addResizeProperty( obj, logoPath, "y" );
	      }
			
   	   var bot:Number = values ? (values.y + values.height) : (media.mediaRegion.y + media.mediaRegion.height);					
	      dashResizer.setResizeProperty( logo, logoPath, "x", flashVars.logox );
	      dashResizer.setResizeProperty( logo, logoPath, "y", (bot - (logo.height + flashVars.logoy)));				      
         break;

      case "ul":
         dashResizer.setResizeProperty( logo, logoPath, "x", flashVars.logox );
         dashResizer.setResizeProperty( logo, logoPath, "y", flashVars.logoy );
	      break;
   		
      case "ur":
	      if( addObject ) {
		      dashResizer.addResizeProperty( obj, logoPath, "x" );
	      }
   	   
	      dashResizer.setResizeProperty( logo, logoPath, "x", (media.mediaRegion.width - (logo.width + flashVars.logox)) );
	      dashResizer.setResizeProperty( logo, logoPath, "y", flashVars.logoy );
	      break;
   		
      case "br":
	      if( addObject ) {
		      dashResizer.addResizeProperty( obj, logoPath, "y" );
		      dashResizer.addResizeProperty( obj, logoPath, "x" );	            
	      }

	      dashResizer.setResizeProperty( logo, logoPath, "x", (media.mediaRegion.width - (logo.width + flashVars.logox)));
	      dashResizer.setResizeProperty( logo, logoPath, "y", (media.mediaRegion.height - (logo.height + flashVars.logoy)));
	      break;
   	   
      default:
         break;	      
   }
}