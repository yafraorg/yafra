/*****************************************************************
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
package org.yafra.rcp;

import org.eclipse.jface.preference.BooleanFieldEditor;
import org.eclipse.jface.preference.DirectoryFieldEditor;
import org.eclipse.jface.preference.FieldEditorPreferencePage;
import org.eclipse.jface.preference.RadioGroupFieldEditor;
import org.eclipse.jface.preference.StringFieldEditor;
import org.eclipse.ui.IWorkbench;
import org.eclipse.ui.IWorkbenchPreferencePage;
import org.eclipse.jface.preference.ComboFieldEditor;

/**
 * @author mwn
 * 
 */
public class Preferences extends FieldEditorPreferencePage implements IWorkbenchPreferencePage
{

	/**
	 * 
	 */
	public Preferences()
		{
		super(GRID);
		setPreferenceStore(Activator.getDefault().getPreferenceStore());
		setDescription("yafra application preferences");
		}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.eclipse.jface.preference.FieldEditorPreferencePage#createFieldEditors
	 * ()
	 */
	@Override
	protected void createFieldEditors()
		{
		addField(new DirectoryFieldEditor(PreferencesConstants.P_PATH, "&Directory preference:", getFieldEditorParent()));
		addField(new BooleanFieldEditor(PreferencesConstants.P_BOOLEAN, "&An example of a boolean preference", getFieldEditorParent()));

		addField(new RadioGroupFieldEditor(PreferencesConstants.P_CHOICE, "An example of a multiple-choice preference", 1, new String[][] { { "&Oracle", "ora" },
				{ "&MySql", "mysql" }, { "&Microsoft SQL Server", "sqlserver" } }, getFieldEditorParent()));
		addField(new StringFieldEditor(PreferencesConstants.P_STRING, "A &text preference:", getFieldEditorParent()));
		addField(new ComboFieldEditor("id", "New ComboFieldEditor", new String[][]{{"name_1", "value_1"}, {"name_2", "value_2"}}, getFieldEditorParent()));
		}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.eclipse.ui.IWorkbenchPreferencePage#init(org.eclipse.ui.IWorkbench)
	 */
	@Override
	public void init(IWorkbench workbench)
		{
		// TODO Auto-generated method stub

		}

}
