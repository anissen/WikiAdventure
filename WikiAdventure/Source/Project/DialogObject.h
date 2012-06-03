
#ifndef DIALOGOBJECT_H
#define DIALOGOBJECT_H

#include <string>
using std::string;

#include <vector>
using std::vector;

/** A ? object */
class CDialogObject
{
private:
	void ShowDialogText ( vector<CDialogObject*>* vDialogs, int iDepth, bool bExpand );

protected:
	string m_sSpeakerID;
	string m_sDialogText;
	string m_sOnLoad;
	string m_sOnClick;
	CDialogObject* m_pParent;
	vector<CDialogObject*> m_vpDialogs;

public:
	CDialogObject();
	virtual ~CDialogObject();

	void LoadContents( const string& sRawItemText );

	/** Insets a child dialog class. 
		@param pDialog Pointer to a CDialogObject class.
	*/
	void AddChildDialog		( CDialogObject* pDialog );

	vector<CDialogObject*>* GetChildren();

	string GetDialogText() { return m_sDialogText; }

	/** Set the parent dialog object to the current dialog.
		@param pParent A pointer to a valid CDialogObject object.
	*/
	void SetParent			( CDialogObject* pParent )	{ if ( pParent ) m_pParent = pParent; }
	/** Get the parent dialog object to the current dialog.
		@return A pointer to the parent dialog.
	*/
	CDialogObject* GetParent() const					{ return m_pParent; }

	CDialogObject* GetRootDialog();

	string GetSpeakerID() { return m_sSpeakerID; }

	string GetOnLoad() { return m_sOnLoad; }
	string GetOnClick() { return m_sOnClick; }

	void ShowDialogText ( bool bExpand );
};

#endif // DIALOGOBJECT_H