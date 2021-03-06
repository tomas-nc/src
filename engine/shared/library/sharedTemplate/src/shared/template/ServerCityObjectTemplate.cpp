//========================================================================
//
// ServerCityObjectTemplate.cpp
//
//IMPORTANT: Any code between //@BEGIN TFD... and //@END TFD... will be
//overwritten the next time the template definition is compiled. Do not
//make changes to code inside these blocks.
//
// copyright 2001 Sony Online Entertainment
//
//========================================================================

#include "sharedTemplate/FirstSharedTemplate.h"
#include "sharedTemplateDefinition/TemplateData.h"
#include "sharedTemplateDefinition/TemplateGlobals.h"
#include "ServerCityObjectTemplate.h"
#include "sharedDebug/DataLint.h"
#include "sharedFile/Iff.h"
#include "sharedTemplateDefinition/ObjectTemplate.h"
#include <stdio.h>



/**
 * Class constructor.
 */
ServerCityObjectTemplate::ServerCityObjectTemplate(const std::string & filename)
//@BEGIN TFD INIT
	: ServerUniverseObjectTemplate(filename)
//@END TFD INIT
{
}	// ServerCityObjectTemplate::ServerCityObjectTemplate

/**
 * Class destructor.
 */
ServerCityObjectTemplate::~ServerCityObjectTemplate()
{
//@BEGIN TFD CLEANUP
//@END TFD CLEANUP
}	// ServerCityObjectTemplate::~ServerCityObjectTemplate

/**
 * Static function used to register this template.
 */
void ServerCityObjectTemplate::registerMe(void)
{
	ObjectTemplateList::registerTemplate(ServerCityObjectTemplate_tag, create);
}	// ServerCityObjectTemplate::registerMe

/**
 * Creates a ServerCityObjectTemplate template.
 *
 * @return a new instance of the template
 */
ObjectTemplate * ServerCityObjectTemplate::create(const std::string & filename)
{
	return new ServerCityObjectTemplate(filename);
}	// ServerCityObjectTemplate::create

/**
 * Returns the template id.
 *
 * @return the template id
 */
Tag ServerCityObjectTemplate::getId(void) const
{
	return ServerCityObjectTemplate_tag;
}	// ServerCityObjectTemplate::getId

/**
 * Returns this template's version.
 *
 * @return the version
 */
Tag ServerCityObjectTemplate::getTemplateVersion(void) const
{
	return m_templateVersion;
} // ServerCityObjectTemplate::getTemplateVersion

/**
 * Returns the highest version of this template or it's base templates.
 *
 * @return the highest version
 */
Tag ServerCityObjectTemplate::getHighestTemplateVersion(void) const
{
	if (m_baseData == NULL)
		return m_templateVersion;
	const ServerCityObjectTemplate * base = dynamic_cast<const ServerCityObjectTemplate *>(m_baseData);
	if (base == NULL)
		return m_templateVersion;
	return std::max(m_templateVersion, base->getHighestTemplateVersion());
} // ServerCityObjectTemplate::getHighestTemplateVersion

//@BEGIN TFD
CompilerIntegerParam * ServerCityObjectTemplate::getCompilerIntegerParam(const char *name, bool deepCheck, int index)
{
	return ServerUniverseObjectTemplate::getCompilerIntegerParam(name, deepCheck, index);
}	//ServerCityObjectTemplate::getCompilerIntegerParam

FloatParam * ServerCityObjectTemplate::getFloatParam(const char *name, bool deepCheck, int index)
{
	return ServerUniverseObjectTemplate::getFloatParam(name, deepCheck, index);
}	//ServerCityObjectTemplate::getFloatParam

BoolParam * ServerCityObjectTemplate::getBoolParam(const char *name, bool deepCheck, int index)
{
	return ServerUniverseObjectTemplate::getBoolParam(name, deepCheck, index);
}	//ServerCityObjectTemplate::getBoolParam

StringParam * ServerCityObjectTemplate::getStringParam(const char *name, bool deepCheck, int index)
{
	return ServerUniverseObjectTemplate::getStringParam(name, deepCheck, index);
}	//ServerCityObjectTemplate::getStringParam

StringIdParam * ServerCityObjectTemplate::getStringIdParam(const char *name, bool deepCheck, int index)
{
	return ServerUniverseObjectTemplate::getStringIdParam(name, deepCheck, index);
}	//ServerCityObjectTemplate::getStringIdParam

VectorParam * ServerCityObjectTemplate::getVectorParam(const char *name, bool deepCheck, int index)
{
	return ServerUniverseObjectTemplate::getVectorParam(name, deepCheck, index);
}	//ServerCityObjectTemplate::getVectorParam

DynamicVariableParam * ServerCityObjectTemplate::getDynamicVariableParam(const char *name, bool deepCheck, int index)
{
	return ServerUniverseObjectTemplate::getDynamicVariableParam(name, deepCheck, index);
}	//ServerCityObjectTemplate::getDynamicVariableParam

StructParamOT * ServerCityObjectTemplate::getStructParamOT(const char *name, bool deepCheck, int index)
{
	return ServerUniverseObjectTemplate::getStructParamOT(name, deepCheck, index);
}	//ServerCityObjectTemplate::getStructParamOT

TriggerVolumeParam * ServerCityObjectTemplate::getTriggerVolumeParam(const char *name, bool deepCheck, int index)
{
	return ServerUniverseObjectTemplate::getTriggerVolumeParam(name, deepCheck, index);
}	//ServerCityObjectTemplate::getTriggerVolumeParam

void ServerCityObjectTemplate::initStructParamOT(StructParamOT &param, const char *name)
{
	if (param.isInitialized())
		return;
	ServerUniverseObjectTemplate::initStructParamOT(param, name);
}	// ServerCityObjectTemplate::initStructParamOT

void ServerCityObjectTemplate::setAsEmptyList(const char *name)
{
	ServerUniverseObjectTemplate::setAsEmptyList(name);
}	// ServerCityObjectTemplate::setAsEmptyList

void ServerCityObjectTemplate::setAppend(const char *name)
{
	ServerUniverseObjectTemplate::setAppend(name);
}	// ServerCityObjectTemplate::setAppend

bool ServerCityObjectTemplate::isAppend(const char *name) const
{
	return ServerUniverseObjectTemplate::isAppend(name);
}	// ServerCityObjectTemplate::isAppend


int ServerCityObjectTemplate::getListLength(const char *name) const
{
	return ServerUniverseObjectTemplate::getListLength(name);
}	// ServerCityObjectTemplate::getListLength

/**
 * Loads the template data from an iff file. We should already be in the form
 * for this template.
 *
 * @param file		file to load from
 */
void ServerCityObjectTemplate::load(Iff &file)
{
static const int MAX_NAME_SIZE = 256;
char paramName[MAX_NAME_SIZE];

	if (file.getCurrentName() != ServerCityObjectTemplate_tag)
	{
		ServerUniverseObjectTemplate::load(file);
		return;
	}

	file.enterForm();
	m_templateVersion = file.getCurrentName();
	if (m_templateVersion == TAG(D,E,R,V))
	{
		file.enterForm();
		file.enterChunk();
		std::string baseFilename;
		file.read_string(baseFilename);
		file.exitChunk();
		const ObjectTemplate *base = ObjectTemplateList::fetch(baseFilename);
		DEBUG_WARNING(base == nullptr, ("was unable to load base template %s", baseFilename.c_str()));
		if (m_baseData == base && base != nullptr)
			base->releaseReference();
		else
		{
			if (m_baseData != nullptr)
				m_baseData->releaseReference();
			m_baseData = base;
		}
		file.exitForm();
		m_templateVersion = file.getCurrentName();
	}
	if (getHighestTemplateVersion() != TAG(0,0,0,0))
	{
		if (DataLint::isEnabled())
			DEBUG_WARNING(true, ("template %s version out of date", file.getFileName()));
	}

	file.enterForm();

	file.enterChunk();
	int paramCount = file.read_int32();
	file.exitChunk();
	UNREF(paramName);
	UNREF(paramCount);

	file.exitForm();
	ServerUniverseObjectTemplate::load(file);
	file.exitForm();
	return;
}	// ServerCityObjectTemplate::load

/**
 * Saves the template data to an iff file.
 *
 * @param file			file to save to
 * @param location		file type (client or server)
 */
void ServerCityObjectTemplate::save(Iff &file)
{
int count;

	file.insertForm(ServerCityObjectTemplate_tag);
	if (m_baseTemplateName.size() != 0)
	{
		file.insertForm(TAG(D,E,R,V));
		file.insertChunk(TAG(X, X, X, X));
		file.insertChunkData(m_baseTemplateName.c_str(), m_baseTemplateName.size() + 1);
		file.exitChunk();
		file.exitForm();
	}
	file.insertForm(TAG(0,0,0,0));
	file.allowNonlinearFunctions();

	int paramCount = 0;


	// write number of parameters
	file.goToTopOfForm();
	file.insertChunk(TAG(P, C, N, T));
	file.insertChunkData(&paramCount, sizeof(paramCount));
	file.exitChunk();

	file.exitForm(true);
	ServerUniverseObjectTemplate::save(file);
	file.exitForm();
	UNREF(count);
}	// ServerCityObjectTemplate::save

//@END TFD
