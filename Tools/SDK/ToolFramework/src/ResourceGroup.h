#ifndef RESOURCEGROUP_H_
#define RESOURCEGROUP_H_

#include <wx/wx.h>
#include <wx/treectrl.h>

enum ResourceType
{
	RESTYPE_TEXTURE,
	RESTYPE_MODEL,
	RESTYPE_TERRAIN
};

struct ResourceGroup
{
	ResourceGroup (ResourceType _type, const wxString& _name)
	{
		name = _name;
		type = _type;
	}

	wxString		name;
	wxIcon			icon;
	wxTreeItemId	item;
	ResourceType	type;
};


struct ResourceItem : public wxTreeItemData
{
	ResourceItem (ResourceType _type, const wxString& _name, const wxString& _actortype)
	{
		type = _type;
		name = _name;
		actortype = _actortype;
	}

	ResourceType	type;
	wxString		name;
	wxString		actortype;
};

#endif