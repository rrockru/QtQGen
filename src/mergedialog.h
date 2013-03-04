#ifndef	_QGEN_MERGE_DIALOG_H_
	#define _QGEN_MERGE_DIALOG_H_

	namespace Ui
	{
		enum
		{
			ID_MERGE_REPLACE = 10600,
			ID_MERGE_SKIP,
			ID_MERGE_CANCEL
		};

		enum
		{
			MERGE_ALL = 1 << 0,
			MERGE_REPLACE = 1 << 1,
			MERGE_SKIP = 1 << 2,
			MERGE_CANCEL = 1 << 30
		};

		class MergeDialog : public QDialog
		{
			Q_OBJECT

			QPushButton	*_replace;
			QPushButton	*_skip;
			QPushButton	*_cancel;
			QCheckBox	*_chkToAll;

			//void OnButton(wxCommandEvent &event);

		public:
			MergeDialog(QWidget *parent, const QString& title, const QString &message);

		private:
			void Done(int);

			private slots:
				void OnReplace();
				void OnSkip();
				void OnCancel();
		};
	}

#endif
