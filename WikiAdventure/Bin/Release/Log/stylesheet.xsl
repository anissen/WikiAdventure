<!--
////////////////////////////////////////////////////////////////////////

 XSL stylesheet template for use with XML files created by XMLLogger

////////////////////////////////////////////////////////////////////////
-->

<!-- 
This stylesheet has been tested with Microsoft IE 5.0 
and MSXML30 SP1 in REPLACE MODE (use xmlinst.exe)
Search "Installing MSXML 3.0 for XSLT Support" in the MSDN Library
-->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="html"/>

   <!--
   ////////////////////////////////////////////////////////////////////////
                               Main Template
   ////////////////////////////////////////////////////////////////////////
   -->
   
   <xsl:template match="/">
   
      <html>

         <head>
            <meta http-equiv="Content-Type" content="text/html; charset=windows-1252"></meta>
            <title><xsl:value-of select="Project/Name" /> Log</title>
            <style>
               h1                   { color: #000080; margin-left: 0 }
               h2                   { color: #000080; margin-left: 0 }
               h3                   { color: #000080; margin-left: 40 }
               h4                   { color: #000080; margin-left: 60 }
               h5                   { color: #000080; margin-left: 80 }
               h6                   { color: #000080; margin-left: 100 }
               .Header1Paragraph    { margin-left: 20 }
               .Header2Paragraph    { margin-left: 00 }
               .Header3Paragraph    { margin-left: 60 }
               .Header4Paragraph    { margin-left: 80 }
               .Header5Paragraph    { margin-left: 100 }
               .Header6Paragraph    { margin-left: 120 }
               a                    { text-decoration: none; color: #000080; }
               table                { border-collapse: collapse; margin-top: 0; }
               td                   { border: 0; }
               th                   {  }
               .PropertyName        { font-weight: bold; }
               .ListHeader          { font-weight: bold; }
	       .RowOdd              { background-color: #FFFFFF; color: #808080; }
	       .RowEven             { background-color: #F5F5F5; color: #000000; }
               body                 { font: 12px Verdana, Arial, Helvetica, sans-serif; }
               tbody                { font: 12px Verdana, Arial, Helvetica, sans-serif; }
	      .code		    { font: 12px Courier New; }
            </style>
         </head>

         <body>

            <!-- This template applies to Project level documentation only -->
            <xsl:apply-templates select="DialogBlocks" />

         </body>

       </html>
   
   </xsl:template>

   <!--
   ////////////////////////////////////////////////////////////////////////
                               Template for Project
   ////////////////////////////////////////////////////////////////////////
   -->
   
   <xsl:template match="DialogBlocks">
     <xsl:for-each select="DialogBlock">

        <p class="Header2Paragraph">
         
          <h2>
            <span class='PropertyName'>Dialog ID: </span>
            <xsl:choose>
               <xsl:when test="DialogID != '' "><xsl:value-of select="DialogID"/></xsl:when>
               <xsl:otherwise>N/A</xsl:otherwise>
            </xsl:choose>
          </h2>

            <span class='PropertyName'>Main Page: </span>
            <xsl:choose>
               <xsl:when test="MainPage != '' "><xsl:value-of select="MainPage"/></xsl:when>
               <xsl:otherwise>N/A</xsl:otherwise>
            </xsl:choose>  
            <br/>

            <span class='PropertyName'>Sub Page: </span>
            <xsl:choose>
               <xsl:when test="SubPage != '' "><xsl:value-of select="SubPage"/></xsl:when>
               <xsl:otherwise>N/A</xsl:otherwise>
            </xsl:choose>  
            <br/><br/>         

            <span class='PropertyName'>Speaker ID: </span>
            <xsl:choose>
               <xsl:when test="SpeakerID != '' "><xsl:value-of select="SpeakerID"/></xsl:when>
               <xsl:otherwise>N/A</xsl:otherwise>
            </xsl:choose>            
            <br/><br/>

            <span class='PropertyName'>Dialog Items: </span>
            <xsl:choose>

               <xsl:when test="count(Dialogs) = 0 ">
                 None (invalid dialog block)
               </xsl:when>

               <xsl:otherwise>
                 <!-- Dialog Items -->
                 <br/>
                 <xsl:apply-templates select="Dialogs">
	         </xsl:apply-templates>
               </xsl:otherwise>

            </xsl:choose> 

         </p>
     </xsl:for-each>
   </xsl:template>


   <!--
   ////////////////////////////////////////////////////////////////////////
                               Template for dialog list
   ////////////////////////////////////////////////////////////////////////
   -->
   
   <xsl:template match="Dialogs">

      <!-- If there is at least one element -->
      <xsl:choose>

         <xsl:when test="count(Dialog) = 0"> None (no sub-dialogs)</xsl:when>

         <xsl:otherwise>
          
               <xsl:for-each select="Dialog">
                 <table width="100%" cellspacing="0" cellpadding="2"><tr>

                    <td width="1" bgcolor="lightblue" align="right" valign="top">
                      <b><xsl:value-of select="position()"/></b>
                    </td>
                    <td bgcolor="white">

                      <!-- Speaker -->
                      <xsl:choose>
                        <xsl:when test="Speaker != ''">
                          <b><xsl:value-of select="SpeakerID"/>:</b><br/>
                        </xsl:when>
                      </xsl:choose>

                      <!-- Dialog Text -->
		      <xsl:value-of select="DialogText"/>

                      <!-- Event OnLoad -->
                      <xsl:choose>
                        <xsl:when test="OnLoad != ''">
                          <br/><font color="blue">Event <b>OnLoad: </b><xsl:value-of select="OnLoad"/></font>
                        </xsl:when>
                      </xsl:choose>

                      <!-- Event OnAfter -->
                      <xsl:choose>
                        <xsl:when test="OnAfter != ''">
                          <br/><font color="blue">Event <b>OnAfter: </b><xsl:value-of select="OnAfter"/></font>
                        </xsl:when>
                      </xsl:choose>

                      <xsl:choose>
                        <xsl:when test="count(Dialogs) != 0">
                          <xsl:apply-templates select="Dialogs">
                          </xsl:apply-templates>
                        </xsl:when> 
                      </xsl:choose>
                   </td>

                   </tr>
                 </table>
               </xsl:for-each>

         </xsl:otherwise>

      </xsl:choose>

   </xsl:template>

</xsl:stylesheet>

<!--
////////////////////////////////////////////////////////////////////////

 End of file

////////////////////////////////////////////////////////////////////////
-->
