/***********************************************************************
	filename: 	CEGUIScheme.h
	created:	21/2/2004
	author:		Paul D Turner
	
	purpose:	Defines abstract base class for the GUI Scheme object.
*************************************************************************/
/***************************************************************************
 *   Copyright (C) 2004 - 2006 Paul D Turner & The CEGUI Development Team
 *
 *   Permission is hereby granted, free of charge, to any person obtaining
 *   a copy of this software and associated documentation files (the
 *   "Software"), to deal in the Software without restriction, including
 *   without limitation the rights to use, copy, modify, merge, publish,
 *   distribute, sublicense, and/or sell copies of the Software, and to
 *   permit persons to whom the Software is furnished to do so, subject to
 *   the following conditions:
 *
 *   The above copyright notice and this permission notice shall be
 *   included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 *   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 *   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 *   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *   OTHER DEALINGS IN THE SOFTWARE.
 ***************************************************************************/
#ifndef _CEGUIScheme_h_
#define _CEGUIScheme_h_

#include "CEGUIBase.h"
#include "CEGUIString.h"
#include "CEGUISchemeManager.h"


#include <vector>


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif


// Start of CEGUI namespace section
namespace CEGUI
{
/*!
\brief
	A class that groups a set of GUI elements and initialises the system to access those elements.

	A GUI Scheme is a high-level construct that loads and initialises various lower-level objects
	and registers them within the system for usage.  So, for example, a Scheme might create some
	Imageset objects, some Font objects, and register a collection of WindowFactory objects within
	the system which would then be in a state to serve those elements to client code.
*/
class CEGUIEXPORT Scheme
{
	friend class Scheme_xmlHandler;
public:
	/*!
	\brief
		Loads all resources for this scheme.

	\return
		Nothing.
	*/
	void	loadResources(void);


	/*!
	\brief
		Unloads all resources for this scheme.  This should be used very carefully.

	\return
		Nothing.
	*/
	void	unloadResources(void);


	/*!
	\brief
		Return whether the resources for this Scheme are all loaded.

	\return
		true if all resources for the Scheme are loaded and available, or false of one or more resource is not currently loaded.
	*/
	bool	resourcesLoaded(void) const;


	/*!
	\brief
		Return the name of this Scheme.

	\return
		String object containing the name of this Scheme.
	*/
	const String& getName(void) const		{return d_name;}

    /*!
    \brief
        Returns the default resource group currently set for Schemes.

    \return
        String describing the default resource group identifier that will be
        used when loading Scheme xml file data.
    */
    static const String& getDefaultResourceGroup()
        { return d_defaultResourceGroup; }

    /*!
    \brief
        Sets the default resource group to be used when loading scheme xml data

    \param resourceGroup
        String describing the default resource group identifier to be used.

    \return
        Nothing.
    */
    static void setDefaultResourceGroup(const String& resourceGroup)
        { d_defaultResourceGroup = resourceGroup; }

private:
	/*************************************************************************
		Implementation Constants
	*************************************************************************/
	static const char	GUISchemeSchemaName[];			//!< Filename of the XML schema used for validating GUIScheme files.

	/*************************************************************************
		Friends
	*************************************************************************/
	friend	Scheme* SchemeManager::loadScheme(const String& scheme_filename, const String& resourceGroup);
	friend	void	SchemeManager::unloadScheme(const String& scheme_name);


	/*************************************************************************
		Construction and Destruction
	*************************************************************************/
	/*!
	\brief
		Creates a scheme object from the data specified in the file \a filename

	\param filename
		String object holding the name of the file to use when creating this Scheme object.

    \param resourceGroup
        Group identifier to be passed to the resource provider when loading the scheme
        specification file.

	\return
		Nothing.
	*/
	Scheme(const String& filename, const String& resourceGroup);

    /*!
    \brief
        Load all XML based imagesets required by the scheme.
    */
    void loadXMLImagesets();

    /*!
    \brief
        Load all image file based imagesets required by the scheme.
    */
    void loadImageFileImagesets();

    /*!
    \brief
        Load all xml based fonts required by the scheme.
    */
    void loadFonts();

    /*!
    \brief
        Load all xml looknfeel files required by the scheme.
    */
    void loadLookNFeels();

    /*!
    \brief
        Register all window factories required by the scheme.
    */
    void loadWindowFactories();

    /*!
    \brief
        Register all window renderer factories required by the scheme.
    */
    void loadWindowRendererFactories();

    /*!
    \brief
        Register all factory aliases required by the scheme.
    */
    void loadFactoryAliases();

    /*!
    \brief
        Create all falagard mappings required by the scheme.
    */
    void loadFalagardMappings();

    /*!
    \brief
        Unload all XML based imagesets created by the scheme.
    */
    void unloadXMLImagesets();

    /*!
    \brief
        Unload all image file based imagesets created by the scheme.
    */
    void unloadImageFileImagesets();

    /*!
    \brief
        Unload all xml based fonts created by the scheme.
    */
    void unloadFonts();

    /*!
    \brief
        Unload all xml looknfeel files loaded by the scheme.
    */
    void unloadLookNFeels();

    /*!
    \brief
        Unregister all window factories registered by the scheme.
    */
    void unloadWindowFactories();

    /*!
    \brief
        Unregister all window renderer factories registered by the scheme.
    */
    void unloadWindowRendererFactories();

    /*!
    \brief
        Unregister all factory aliases created by the scheme.
    */
    void unloadFactoryAliases();

    /*!
    \brief
        Unregister all falagard mappings created by the scheme.
    */
    void unloadFalagardMappings();

    /*!
    \brief
        Check state of all XML based imagesets created by the scheme.
    */
    bool areXMLImagesetsLoaded() const;

    /*!
    \brief
        Check state of all image file based imagesets created by the scheme.
    */
    bool areImageFileImagesetsLoaded() const;

    /*!
    \brief
        Check state of all xml based fonts created by the scheme.
    */
    bool areFontsLoaded() const;

    /*!
    \brief
        Check state of all looknfeel files loaded by the scheme.
    */
    bool areLookNFeelsLoaded() const;

    /*!
    \brief
        Check state of all window factories registered by the scheme.
    */
    bool areWindowFactoriesLoaded() const;

    /*!
    \brief
        Check state of all window renderer factories registered by the scheme.
    */
    bool areWindowRendererFactoriesLoaded() const;

    /*!
    \brief
        Check state of all factory aliases created by the scheme.
    */
    bool areFactoryAliasesLoaded() const;

    /*!
    \brief
        Check state of all falagard mappings created by the scheme.
    */
    bool areFalagardMappingsLoaded() const;

public:		// for luabind compatibility
	/*!
	\brief
		Destroys a Scheme object

	\return
		Nothing
	*/
	~Scheme(void);


private:
	/*************************************************************************
		Structs used to hold scheme information
	*************************************************************************/
	struct LoadableUIElement
	{
		String	name;
		String	filename;
        String  resourceGroup;
	};

	struct	UIElementFactory
	{
		String name;
	};

	struct	UIModule
	{
		String name;
		FactoryModule*	module;
		std::vector<UIElementFactory>	factories;
	};

	struct AliasMapping
	{
		String aliasName;
		String targetName;
	};

    struct FalagardMapping
    {
        String windowName;
        String targetName;
        String rendererName;
        String lookName;
    };

	/*************************************************************************
		Implementation Data
	*************************************************************************/
	String	d_name;			//!< the name of this scheme.

	std::vector<LoadableUIElement>		d_imagesets;
	std::vector<LoadableUIElement>		d_imagesetsFromImages;
	std::vector<LoadableUIElement>		d_fonts;
	std::vector<UIModule>				d_widgetModules;
    std::vector<UIModule>               d_windowRendererModules;
	std::vector<AliasMapping>			d_aliasMappings;
    std::vector<LoadableUIElement>		d_looknfeels;
    std::vector<FalagardMapping>        d_falagardMappings;

    static String d_defaultResourceGroup;   //!< holds default resource group
};

} // End of  CEGUI namespace section

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	// end of guard _CEGUIScheme_h_
