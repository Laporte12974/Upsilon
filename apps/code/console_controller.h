#ifndef CODE_CONSOLE_CONTROLLER_H
#define CODE_CONSOLE_CONTROLLER_H

#include <escher.h>
#include <python/port/port.h>

#include "console_edit_cell.h"
#include "console_line_cell.h"
#include "console_store.h"
#include "script_store.h"

namespace Code {

class ConsoleController : public ViewController, public ListViewDataSource, public SelectableTableViewDataSource, public SelectableTableViewDelegate, public TextFieldDelegate, public MicroPython::ExecutionEnvironment {
public:
  static constexpr KDText::FontSize k_fontSize = KDText::FontSize::Large;

  ConsoleController(Responder * parentResponder, ScriptStore * scriptStore);
  ~ConsoleController();
  ConsoleController(const ConsoleController& other) = delete;
  ConsoleController(ConsoleController&& other) = delete;
  ConsoleController operator=(const ConsoleController& other) = delete;
  ConsoleController& operator=(ConsoleController&& other) = delete;

  bool loadPythonEnvironment();
  void unloadPythonEnvironment();
  bool pythonEnvironmentIsLoaded();

  void autoImport();
  void runAndPrintForCommand(const char * command);
  void removeExtensionIfAny(char * name);

  // ViewController
  View * view() override { return &m_selectableTableView; }
  void viewWillAppear() override;
  void didBecomeFirstResponder() override;
  bool handleEvent(Ion::Events::Event event) override;
  ViewController::DisplayParameter displayParameter() override { return ViewController::DisplayParameter::WantsMaximumSpace; }

  // ListViewDataSource
  int numberOfRows() override;
  KDCoordinate rowHeight(int j) override;
  KDCoordinate cumulatedHeightFromIndex(int j) override;
  int indexFromCumulatedHeight(KDCoordinate offsetY) override;
  HighlightCell * reusableCell(int index, int type) override;
  int reusableCellCount(int type) override;
  int typeAtLocation(int i, int j) override;
  void willDisplayCellAtLocation(HighlightCell * cell, int i, int j) override;

  // SelectableTableViewDelegate
  void tableViewDidChangeSelection(SelectableTableView * t, int previousSelectedCellX, int previousSelectedCellY) override;

  // TextFieldDelegate
  bool textFieldShouldFinishEditing(TextField * textField, Ion::Events::Event event) override;
  bool textFieldDidReceiveEvent(TextField * textField, Ion::Events::Event event) override;
  bool textFieldDidFinishEditing(TextField * textField, const char * text, Ion::Events::Event event) override;
  bool textFieldDidAbortEditing(TextField * textField, const char * text) override;
  ::Toolbox * toolboxForTextField(TextField * textField) override;
  // MicroPython::ExecutionEnvironment
  void printText(const char * text, size_t length) override;

private:
  static constexpr int LineCellType = 0;
  static constexpr int EditCellType = 1;
  static constexpr int k_numberOfLineCells = 15; // May change depending on the screen height
  static constexpr int k_pythonHeapSize = 16384;
  static constexpr int k_outputAccumulationBufferSize = 100;
  void autoImportScriptAtIndex(int index);
  void flushOutputAccumulationBufferToStore();
  void appendTextToOutputAccumulationBuffer(const char * text, size_t length);
  void emptyOutputAccumulationBuffer();
  int firstNewLineCharIndex(const char * text, size_t length);
  StackViewController * stackViewController();
  bool copyCurrentLineToClipboard();
  int m_rowHeight;
  ConsoleStore m_consoleStore;
  SelectableTableView m_selectableTableView;
  ConsoleLineCell m_cells[k_numberOfLineCells];
  ConsoleEditCell m_editCell;
  char * m_pythonHeap;
  char m_outputAccumulationBuffer[k_outputAccumulationBufferSize];
  /* The Python machine might call printText several times to print a single
   * string. We thus use m_outputAccumulationBuffer to store and concatenate the
   * different strings until a new line char appears in the text. When this
   * happens, or when m_outputAccumulationBuffer is full, we create a new
   * ConsoleLine in the ConsoleStore and empty m_outputAccumulationBuffer. */
  ScriptStore * m_scriptStore;
};
}

#endif
