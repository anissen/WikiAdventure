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
               h2                   { color: #000080; margin-left: 20 }
               h3                   { color: #000080; margin-left: 40 }
               h4                   { color: #000080; margin-left: 60 }
               h5                   { color: #000080; margin-left: 80 }
               h6                   { color: #000080; margin-left: 100 }
               .Header1Paragraph    { margin-left: 20 }
               .Header2Paragraph    { margin-left: 40 }
               .Header3Paragraph    { margin-left: 60 }
               .Header4Paragraph    { margin-left: 80 }
               .Header5Paragraph    { margin-left: 100 }
               .Header6Paragraph    { margin-left: 120 }
               a                    { text-decoration: none; color: #000080 }
               table                { border-collapse: collapse; margin-top: 10; }
               td                   { border: 1 solid #000060; }
               th                   { color: #FFFFFF; background-color: #000060; text-align: left; }
               .PropertyName        { font-weight: bold }
               .ListHeader          { font-weight: bold }
	       .RowOdd              { background-color: #FFFFFF }
	       .RowEven             { background-color: #F5F5F5 }
               body                 { font: 12px Verdana, Arial, Helvetica, sans-serif; }
               tbody                { font: 12px Verdana, Arial, Helvetica, sans-serif; }
	      .code		    { font: 12px Courier New; }
            </style>
         </head>

         <body>

            <!-- This template applies to Project level documentation only -->
            <xsl:apply-templates select="Project" />

         </body>

       </html>
   
   </xsl:template>

   <!--
   ////////////////////////////////////////////////////////////////////////
                               Template for Project
   ////////////////////////////////////////////////////////////////////////
   -->
   
   <xsl:template match="Project"> 
         <h1>
            <!-- Add the logical name -->
            <xsl:value-of select="Name"/>
         </h1>

         <p class="Header1Paragraph">

            <span class='PropertyName'>Main source code directory: </span>
            <xsl:choose>
               <xsl:when test="MainSourceDir != '' "><xsl:value-of select="MainSourceDir"/></xsl:when>
               <xsl:otherwise>N/A</xsl:otherwise>
            </xsl:choose>            
            <br/>
            <br/>

            <xsl:if test="Compiled != '' ">
                <span class='PropertyName'>Compiled: </span><xsl:value-of select="Compiled"/><br/>
            </xsl:if>
            <br/>

            <span class='PropertyName'>Command line arguments: </span>

            <xsl:choose>
               <xsl:when test="count(CmdArguments/CmdArgument) = 0"> None<br/><br/></xsl:when>
               <xsl:otherwise>
                  <br/>
                  <xsl:for-each select="CmdArguments/CmdArgument">
                     <strong>Argument <xsl:value-of select="position()"/>: </strong> <xsl:value-of select="."/><br/>
                  </xsl:for-each>
               </xsl:otherwise>
            </xsl:choose>
            <br/>

            <span class='PropertyName'>Comment: </span>
            <xsl:choose>
               <xsl:when test="count(CommentLines/CommentLine) = 0"> None<br/><br/></xsl:when>
               <xsl:otherwise>
                  <br/>
		  <span class='code'>
                  <xsl:for-each select="CommentLines/CommentLine">
                     <xsl:value-of select="."/>
                     <br/>
                  </xsl:for-each>
		  </span>
                  <br/>
               </xsl:otherwise>
            </xsl:choose>


            <!-- Build the Procedures table -->
            <xsl:apply-templates select="Files">
						
 	    </xsl:apply-templates>          


         <hr/>
         <br/>

	 <xsl:apply-templates select="LogEntries">
	 </xsl:apply-templates>  

         </p>
   
   </xsl:template>


   <!--
   ////////////////////////////////////////////////////////////////////////
                               Template for log entry list
   ////////////////////////////////////////////////////////////////////////
   -->
   
   <xsl:template match="LogEntries">

      <span class='ListHeader'>Log entries:</span>

      <!-- If there is at least one element -->
      <xsl:choose>

         <xsl:when test="count(LogEntry) = 0"> None</xsl:when>

         <xsl:otherwise>

            <table border="0" width="98%" cellpadding="3">
                  
               <tr>
 		  <th width="200">Timestamp</th>
                  <th width="100">Debug Type</th>
                  <th width="200">Function</th>
                  <th>Description</th>
               </tr>

               <xsl:for-each select="LogEntry">

		<tr>
		<xsl:choose>
		   <xsl:when test = "position() mod 2 = 0">
		      <xsl:attribute name='class'>RowEven</xsl:attribute>
		   </xsl:when>
		   <xsl:otherwise>
		      <xsl:attribute name='class'>RowOdd</xsl:attribute>
		   </xsl:otherwise>
		</xsl:choose>

                     <td>
                        <xsl:attribute name='title'>Log entry #<xsl:value-of select="position()"/></xsl:attribute>
                        <xsl:value-of select="Timestamp"/>
                     </td>
		     
                     <td>
                        <xsl:choose>
                           <xsl:when test="DebugType='Info'">
                              <font color="blue">Information</font>
                           </xsl:when>
                           <xsl:when test="DebugType='Warning'">
                              <font color="orange">Warning</font>
                           </xsl:when>
                           <xsl:when test="DebugType='Error'">
                              <font color="red">Error</font>
                           </xsl:when>
                           <xsl:when test="DebugType='Critical'">
                              <font color="darkred"><strong>Critical Error</strong></font>
                           </xsl:when>
                        </xsl:choose>                
                     </td>

		     <td>
                        <xsl:attribute name='title'>File: <xsl:value-of select="File"/>  (Line <xsl:value-of select="Line"/>)</xsl:attribute>
                        <xsl:value-of select="ClassName"/>::<i><xsl:value-of select="FuncName"/></i>
                     </td>

                     <td><xsl:value-of select="Info"/></td>
                  </tr>
               </xsl:for-each>

            </table>

         </xsl:otherwise>

      </xsl:choose>
      
   </xsl:template>

</xsl:stylesheet>

<!--
////////////////////////////////////////////////////////////////////////

 End of file

////////////////////////////////////////////////////////////////////////
-->
